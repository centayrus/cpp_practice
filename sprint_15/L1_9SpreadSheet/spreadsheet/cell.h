#pragma once

#include "common.h"
#include "formula.h"
#include "sheet.h"

#include <string>
#include <memory>

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

class Sheet; 

class Cell : public CellInterface {
public:

    Cell(Sheet &sheet);
    ~Cell();

    void Set(std::string text);
    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;

private:
    std::unique_ptr<Impl> impl_ = nullptr;
    Sheet &sheet_;
};