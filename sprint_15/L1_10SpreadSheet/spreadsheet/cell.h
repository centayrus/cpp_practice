#pragma once

#include "common.h"
#include "formula.h"

#include "sheet.h"

#include <forward_list>
#include <optional>
#include <string>

class Impl {
public:
    Impl() = default;

    virtual ~Impl() = default;

    virtual std::string GetValue() const = 0;
};

class EmptyImpl : public Impl {
public:
    EmptyImpl() = default;

    ~EmptyImpl() override = default;

    std::string GetValue() const override {
        return empty_string_;
    }

private:
    std::string empty_string_ = "";

};

class TextImpl : public Impl {
public:
    TextImpl(std::string text) : str_(std::move(text)) {
    }

    ~TextImpl() override = default;

    std::string GetValue() const override {
        return str_;
    }

private:
    std::string str_;
};

class FormulaImpl : public Impl {
public:
    FormulaImpl(std::string text) : formula_(std::move(text)) {
    }

    ~FormulaImpl() override = default;

    std::string GetValue() const override {
        return formula_;
    }

private:
    std::string formula_;
};

class Cell : public CellInterface {
public:
    Cell(Sheet sheet) sheet_(sheet);
    ~Cell();

    void Clear();

    void Set(std::string text);

    Value GetValue() const override;

    std::string GetText() const override;

    // вернет элементы из объекта std::unique_ptr<FormulaInterface> после парсинга выражения
    std::vector<Position> Cell::GetReferencedCells() const;

    // метод проверяет, что структура формул не имеет циклов
    // вызывается в методе Sheet::SetCell(), если возвращает true,
    // выбрасываем исключение CircularDependencyException,
    // данные поля не изменяются. Использовать алгоритм BFS
    bool IsCycleDetected(const std::forward_list<Position> ptr_to);

    // дополняет ptr_from_ ячейкой, от которой зависит текущая
    void AddDependCell(const Position& pos);

private:
    std::unique_ptr<Impl> impl_ = nullptr;
    mutable std::optional<FormulaInterface::Value> cache_value_; // кеш устанавливается в методе GetValue()
    Sheet &sheet_;
    std::forward_list<Position> ptr_to_;   // позиции ячеек, на которые ссылается текущая,
                                           // заполняется в методе Set в лексическом анализаторе
    std::forward_list<Position> ptr_from_; // * это ячейки, которые ссылаются на текущую, заполняются в методе GetValue()
                                           // позиции ячеек, чей кеш нужно инвалидировать, т.к. текщая ячейка изменила значение

    // внутренний метод для инвалидации кеша ячеек связанных с текущей
    // вызывается в методах Clear(), GetValue() - 
    // устанавливает в null поле optional.
    void CacheInvalidator(const std::forward_list<Position> &ptr_from);
};