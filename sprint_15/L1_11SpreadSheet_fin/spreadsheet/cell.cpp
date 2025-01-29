#include "cell.h"

#include <cassert>
#include <iostream>
#include <optional>
#include <string>

// Реализуйте следующие методы

Cell::Cell(Sheet &sheet, Position pos) : sheet_(sheet), impl_(nullptr), cur_pos_(pos) {};

Cell::~Cell() {
    impl_.reset();
}

void Cell::Set(std::string text) {
   // if (text == GetText()) {
     //   return;
    //}
    if (text[0] == '=' && text.size() > 1) {
        std::string value = "=";
        std::unique_ptr<FormulaInterface> formula = ParseFormula(text.substr(1));
        auto expression = formula->GetExpression();
        referenced_cells_ = formula->GetReferencedCells();
        // здесь добавить проверку на цикличность

        FillDependCells();
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
    if (cache_value_.has_value()) {
        Cell::Value res;
        if (std::holds_alternative<double>(cache_value_.value())) {
            res = std::get<double>(cache_value_.value());
        } else if (std::holds_alternative<FormulaError>(cache_value_.value())) {
            res = std::get<FormulaError>(cache_value_.value());
        }
        return res;
    }
    auto str = impl_->GetValue();
    if (str[0] == '=' && str.size() > 1) {
        auto eval = ParseFormula(str.substr(1))->Evaluate(sheet_);
        if (std::holds_alternative<double>(eval)) {
            cache_value_ = std::get<double>(eval);
            return std::get<double>(eval);
        }
        cache_value_ = std::get<FormulaError>(eval);
        return std::get<FormulaError>(eval);
    } else if (str[0] == '\'') {
        return str.substr(1);
    }
    return str;
}

std::string Cell::GetText() const {
    return impl_->GetValue();
}

std::vector<Position> Cell::GetReferencedCells() const {
    return referenced_cells_;
}

// void Cell::CacheInvalidator(const std::vector<Position> &ptr_from);

void Cell::FillDependCells() {
    auto &sheet = sheet_.GetCellsSet();
    for (auto &cell : referenced_cells_) {
        sheet.at(cell.row).at(cell.col)->AppendDependCell(cur_pos_);
    }
}

void Cell::AppendDependCell(Position pos) {
    depend_cells_.emplace_back(pos);
}