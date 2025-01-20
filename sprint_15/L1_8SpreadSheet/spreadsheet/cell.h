#pragma once

#include "common.h"
#include "formula.h"

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
    Cell();
    ~Cell();

    void Set(std::string text);
    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;

private:
    // можете воспользоваться нашей подсказкой, но это необязательно.
    /* class Impl;
    class EmptyImpl;
    class TextImpl;
    class FormulaImpl; */
    std::unique_ptr<Impl> impl_;
};