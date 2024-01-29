#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int EffectiveCount(const vector<int> &v, int n, int i) {
    if (i > n) {
        return n;
    }
    int result;
    auto iter_end = find_if(v.begin(), v.end(), [&i](const int &el) {
        return el > i;
    });
    int find_result = iter_end - v.begin();

    auto upper = std::upper_bound(v.begin(), v.end(), i);
    int upper_result = upper - v.begin();

    if (find_result <= log2(v.size())) {
        result = find_result;
        cout << "Using find_if"s << endl;
    } else {
        result = upper_result;
        cout << "Using upper_bound"s << endl;
    }
    return result;
}

int main() {
    static const int NUMBERS = 1'000'000;
    static const int MAX = 1'000'000'000;

    mt19937 r;
    uniform_int_distribution<int> uniform_dist(0, MAX);

    vector<int> nums;
    for (int i = 0; i < NUMBERS; ++i) {
        int random_number = uniform_dist(r);
        nums.push_back(random_number);
    }
    sort(nums.begin(), nums.end());

    int i;
    cin >> i;
    int result = EffectiveCount(nums, MAX, i);
    cout << "Total numbers before "s << i << ": "s << result << endl;
}