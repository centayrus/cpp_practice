#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <cmath>

using namespace std;

int main() {
    const auto min = numeric_limits<int64_t>::min();     // минимальное значение типа int64_t
    const auto max = numeric_limits<uint64_t>::max(); // максимальное значение типа uint64_t
    cout << min << endl;
    cout << max << endl;
    auto sum = min + max;
<<<<<<< HEAD
  //  auto min2 = (min);
  //  auto max2 = 2*(max);
    cout << sum << endl;
  //  cout << min2 << endl;
   // cout << max2 << endl;
=======
    auto min2 = 2*(min);
    auto max2 = 2*(max);
    cout << sum << endl;
    cout << min2 << endl;
    cout << max2 << endl;
>>>>>>> main

    // выведите 5 чисел
}
