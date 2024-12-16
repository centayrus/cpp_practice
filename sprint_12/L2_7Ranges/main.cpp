#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <string_view>

namespace rng = std::ranges;
using namespace std;

//template <rng::input_range Range>
void Print(const rng::input_range auto& range) {
    for (const auto& x : range) {
        cout << x << " "sv;
    }
    cout << endl;
}

int main() {
    vector v = { 4, 1, 7, 2, 3, 8 };
    rng::reverse(v);
    Print(v);
    //Print(2);
    return 0;
}