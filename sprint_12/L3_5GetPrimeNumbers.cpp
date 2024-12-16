#include <cmath>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

// не самый эффективный тест на простоту числа
bool IsPrime(int n) {
    if (std::abs(n) < 2) {
        return false;
    }

    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

template<typename OutputIt>
void GetPrimeNumbers(int from, int to, OutputIt output_iter) {
    for (int i = from; i < to; ++i) {
        if (IsPrime(i)) {
            *output_iter++ = i;
        }
    }
}

int main() {
    // результат выведен в cout через пробел
    GetPrimeNumbers(0, 100, ostream_iterator<int>(cout, " "));
} 