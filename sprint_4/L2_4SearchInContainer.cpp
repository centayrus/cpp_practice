#include <iostream>
#include <iterator>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
    // set<int>::const_iterator — тип итераторов для константного множества целых чисел
    auto lower = numbers.lower_bound(border);
    if (numbers.empty()) {
        return numbers.end();
    }
    else if (lower == numbers.end()) {
        auto prev_lower = prev(lower,1);
        return prev_lower;
    }
    else if (lower != numbers.begin()) {
        auto prev_lower = prev(lower, 1);
        if ((*lower - border) >= (border - *prev_lower)) {
            return prev_lower;
        }
    } 

    return lower;
}

int main() {
    set<int> numbers = {1, 4, 6};
    cout << *FindNearestElement(numbers, 0) << " " << *FindNearestElement(numbers, 3) << " "
         << *FindNearestElement(numbers, 5) << " " << *FindNearestElement(numbers, 6) << " "
         << *FindNearestElement(numbers, 100) << endl;
  //  cout << "s: "s;
    // for (const auto s : numbers) {
    //     cout << s << " "s;
    // }
//cout << endl;
    set<int> empty_set;
    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  //  cout << "Эталон: 1 4 4 6 6"s << endl;
    return 0;
}