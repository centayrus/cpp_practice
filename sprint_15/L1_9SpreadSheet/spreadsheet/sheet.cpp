#include "sheet.h"

#include "cell.h"
#include "common.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <optional>

using namespace std::literals;

Sheet::~Sheet() {}

void Sheet::SetCell(Position pos, std::string text) {
    if (!pos.IsValid()) {
        throw InvalidPositionException;
    }

    cells_[pos.row][pos.col].Set(text);

    Sheet::PrintableSizeRenew(pos);
}

const CellInterface *Sheet::GetCell(Position pos) const {
    if (!pos.IsValid()) {
        throw InvalidPositionException;
    }
    return cells_[pos.row][pos.col];
}
CellInterface *Sheet::GetCell(Position pos) {
    if (!pos.IsValid()) {
        throw InvalidPositionException;
    }
    return cells_[pos.row][pos.col];
}

void Sheet::ClearCell(Position pos) {
    cells_[pos.row][pos.col].Clear();
}

Size Sheet::GetPrintableSize() const {
    return print_size_;
}

void Sheet::PrintValues(std::ostream &output) const {
    for (const int row : print_size_.rows) {
        for (const int col : print_size_.cols) {
            output << cells_[row][col].GetText() << '\t';
        }
        output << '\n';
    }
}

void Sheet::PrintTexts(std::ostream &output) const {
    for (int row = 0; row < print_size_.rows; ++row) {
        for (int col = 0; col < print_size_.cols; ++col) {
            output << cells_[row][col].GetValue() << '\t';
        }
        output << '\n';
    }
}

std::unique_ptr<SheetInterface> CreateSheet() {
    return std::make_unique<Sheet>();
}