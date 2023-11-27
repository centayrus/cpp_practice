#include <cstdint>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

int main() {
    const auto min = numeric_limits<int64_t>::min;     // минимальное значение типа int64_t
    const auto max = numeric_limits<uint64_t>::max; // максимальное значение типа uint64_t
    cout << "min = "s << min << endl;
    cout << "max = "s << max << endl;
    auto sum = min + max;
    auto min2 = min*2;
    auto max2 = max*2; 
    cout << "min + max = "s << min + max << endl;
    cout << "min*2 = "s << min2 << endl;
    cout << "max*2 = "s << max2 << endl;

    // выведите 5 чисел
}
