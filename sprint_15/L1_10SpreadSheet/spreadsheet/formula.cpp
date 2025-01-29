#include "formula.h"

#include "FormulaAST.h"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <sstream>
#include <stdexcept>

using namespace std::literals;

std::ostream &operator<<(std::ostream &output, FormulaError fe) {
    return output << "#ARITHM!";
}



namespace {
class Formula : public FormulaInterface {
public:
    // Реализуйте следующие методы:
    explicit Formula(std::string expression) try
        : ast_(ParseFormulaAST(std::move(expression))) {
    } catch (const std::runtime_error &) {
        throw;
    }

    Value Evaluate(const SheetInterface& sheet) const override {
        try {
            return ast_.Execute(sheet);
        } catch (const FormulaError &fe) {
            return fe; // Возвращаем ошибку
        }
    }

    std::string GetExpression() const override {
        std::ostringstream out;
        ast_.PrintFormula(out);
        return out.str();
    }

    std::vector<Position> GetReferencedCells() const override;

private:
    FormulaAST ast_;
};
} // namespace

std::unique_ptr<FormulaInterface> ParseFormula(std::string expression) {
    return std::make_unique<Formula>(std::move(expression));
}