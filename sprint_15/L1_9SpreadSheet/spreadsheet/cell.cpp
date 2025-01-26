#include "cell.h"

#include <cassert>
#include <iostream>
#include <optional>
#include <string>

// Реализуйте следующие методы

Cell::Cell() = default;

Cell::~Cell() {
    impl_.reset();
}

void Cell::Set(std::string text) {
    if (text[0] == '=' && text.size() > 1) {
        std::string value = "=";
        auto expression = ParseFormula(text.substr(1))->GetExpression();
        value += expression;
        impl_ = std::make_unique<FormulaImpl>(value);
    } else {
        impl_ = std::make_unique<TextImpl>(text);
    }
}

void Cell::Clear() {
    impl_.reset();
}

Cell::Value Cell::GetValue() const {
    auto str = impl_->GetValue();
    if (str[0] == '=' && str.size() > 1) {
        auto eval = ParseFormula(str.substr(1))->Evaluate();
        if (std::holds_alternative<double>(eval)) {
            return std::get<double>(eval);
        }
        return std::get<FormulaError>(eval);
    } else if (str[0] == '\'') {
        return str.substr(1);
    }
    return str;
}

std::string Cell::GetText() const {
    return impl_->GetValue();
}
