#pragma once
#include "date.h"
#include <iostream>
#include <string>

struct DayInfo {
    long double earnings;
    double spend;
};

class BudgetManager {
public:
    inline static const Date START_DATE = Date(std::string("2000-01-01"));
    inline static const Date END_DATE = Date(std::string("2100-01-01"));

    // разработайте класс BudgetManager
    BudgetManager()
        : all_days_(START_DATE.ComputeDistance(START_DATE, END_DATE), DayInfo()) {
        // std::cout << "all_days_ size: " << all_days_.size() << '\n';
    }

    void ComputeIncome(const Date from, const Date to) const;
    void Earn(const Date from, const Date to, long double earnings);
    void PayTax(const Date from, const Date to, long double tax);
    const std::vector<DayInfo> GetEarnings() const;
    void Spend(const Date from, const Date to, double spend);

private:
    std::vector<DayInfo> all_days_;
};