#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

// не меняйте файлы json.h и json.cpp
#include "json.h"

using namespace std;

// структура хранит информацию о трате:
// категорию товара или услуги и стоимость
struct Spending {
    string category;
    int amount;
};

int CalculateTotalSpendings(const vector<Spending>& spendings) {
    return accumulate(
        spendings.begin(), spendings.end(), 0, [](int current, const Spending& spending){
            return current + spending.amount;
        });
}

string FindMostExpensiveCategory(const vector<Spending>& spendings) {
    assert(!spendings.empty());
    auto compare_by_amount = [](const Spending& lhs, const Spending& rhs) {
        return lhs.amount < rhs.amount;
    };
    return max_element(begin(spendings), end(spendings), compare_by_amount)->category;
}

vector<Spending> LoadFromJson(istream& input) {
    Document doc = Load(input);
    vector<Spending> result;
    for (auto i : doc.GetRoot().AsArray()) {
        Spending tmp_spend;
        tmp_spend.amount = i.AsMap().at("amount"s).AsInt();
        tmp_spend.category = i.AsMap().at("category"s).AsString();
        result.push_back(tmp_spend);
    }
    return result;
}

int main() {
    // не меняйте main
    const vector<Spending> spendings = LoadFromJson(cin);
    cout << "Total "sv << CalculateTotalSpendings(spendings) << '\n';
    cout << "Most expensive is "sv << FindMostExpensiveCategory(spendings) << '\n';
}
