#include "budget_manager.h"
#include "parser.h"

#include <iostream>
#include <string_view>
#include <stdexcept>

using namespace std;

void ParseAndProcessQuery(BudgetManager& manager, string_view line) {
    // разработайте функцию чтения и обработки запроса
    string_view query_type = line.substr(0, line.find_first_of(' '));
    if (query_type == "Earn"sv) {
        ParserModify query(line);
        manager.Earn(query.GetDateFrom(), query.GetDateTo(), query.GetEarnings());
    }
    else if (query_type == "ComputeIncome"sv) {
        ParserRead query(line);
        manager.ComputeIncome(query.GetDateFrom(), query.GetDateTo());
    }
    else if (query_type == "PayTax"sv) {
        ParserModify query(line);
        manager.PayTax(query.GetDateFrom(), query.GetDateTo(), query.GetTax());
    }
    else if (query_type == "Spend"sv) {
        ParserModify query(line);
        manager.Spend(query.GetDateFrom(), query.GetDateTo(), query.GetSpend());
    }
    else {
        invalid_argument("Wrong query");
    }
}

int ReadNumberOnLine(istream& input) {
    std::string line;
    std::getline(input, line);
    return std::stoi(line);
}

int main() {
    BudgetManager manager;

    const int query_count = ReadNumberOnLine(cin);
    for (int i = 0; i < query_count; ++i) {
        std::string line;
        std::getline(cin, line);
        ParseAndProcessQuery(manager, line);
    }
}