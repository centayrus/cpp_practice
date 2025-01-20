#pragma once

#include "cell.h"
#include "common.h"

#include <functional>
#include <vector>

using CellsSet = std::vector<std::vector<Cell>>;

class Sheet : public SheetInterface {
public:
    Sheet() : print_size_(),
    cells_(Position::MAX_ROWS)
    {

    }

    ~Sheet();

    void SetCell(Position pos, std::string text) override;

    const CellInterface *GetCell(Position pos) const override;
    CellInterface *GetCell(Position pos) override;

    void ClearCell(Position pos) override;

    Size GetPrintableSize() const override;

    void PrintValues(std::ostream &output) const override;
    void PrintTexts(std::ostream &output) const override;

    // Можете дополнить ваш класс нужными полями и методами

private:
    // Можете дополнить ваш класс нужными полями и методами
    CellsSet cells_;
    Size print_size_;
    std::unique_ptr<SheetInterface> sheet_ = nullptr;

    void PrintableSizeRenew(Position pos) {
        if (pos.col + 1 > print_size_.cols) {
            print_size_.cols = pos.col + 1;
        }
        if (pos.row + 1 > print_size_.rows) {
            print_size_.cols = pos.row + 1;
        }
    }
};