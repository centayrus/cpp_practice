#include "budget_manager.h"
#include <iomanip>
#include <iostream>
// разработайте менеджер личного бюджета самостоятельно

void BudgetManager::ComputeIncome(const Date from, const Date to) const {
    long double result = 0.0;
    const int start = from.ComputeDistance(START_DATE, from);
    const int end = to.ComputeDistance(START_DATE, to);
    for (int i = start; i <= end;++i) {
        result += all_days_[i].earnings;
    
    }
    std::cout << std::setprecision(6) << result << std::endl;
    // std::cout << "day_start: " << start << ", day_end: " << end << ", days_all: " << end - start + 1
    //     << ", result: " << result << std::endl;
}

void BudgetManager::Earn(const Date from, const Date to, long double earnings) {
    const int start = from.ComputeDistance(START_DATE, from);
    const int end = to.ComputeDistance(START_DATE, to);
    long double period = end - start + 1;
    long double new_val = earnings / period;
    for (int i = start; i <= end;++i) {
        all_days_[i].earnings += new_val;
        
    }
}

void BudgetManager::PayTax(const Date from, const Date to, long double tax) {
    const int start = from.ComputeDistance(START_DATE, from);
    const int end = to.ComputeDistance(START_DATE, to);
   // long double temp_val;
    for (int i = start; i <= end;++i) {
       // temp_val = all_days_[i].earnings;
        all_days_[i].earnings *= tax;
        
    }
}
const std::vector<DayInfo> BudgetManager::GetEarnings() const {
    return all_days_;
}