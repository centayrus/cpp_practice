#include "budget_manager.h"
#include "parser.h"

#include <iostream>
#include <stdexcept>
#include <string_view>

using namespace std;

void ParseAndProcessQuery(BudgetManager &manager, string_view line) {
    // разработайте функцию чтения и обработки запроса
    string_view query_type = line.substr(0, line.find_first_of(' '));
    line.remove_prefix(query_type.size() + 1);
    if (query_type == "Earn"sv) {
        ParserModify query(line);
        manager.Earn(query.GetDateFrom(), query.GetDateTo(), query.GetEarnings());
    } else if (query_type == "ComputeIncome"sv) {
        ParserRead query(line);
        manager.ComputeIncome(query.GetDateFrom(), query.GetDateTo());
       // auto earn = manager.GetEarnings();
        //  double result = 0.;
        //  for (auto i = 4955; i <= 9611; i++) {
        //     result += earn[i].earnings;
        //  }
        //  std::cout << "self compute: " << result << '\n';
       // manager.ComputeIncome(4956, 9611);
    } else if (query_type == "PayTax"sv) {
        ParserModify query(line);
        manager.PayTax(query.GetDateFrom(), query.GetDateTo(), TAX);
    } else {
        invalid_argument("Wrong query");
    }
}

int ReadNumberOnLine(istream &input) {
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