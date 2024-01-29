#include <cstdint>
#include <iostream>

using namespace std;

// упростите эту экспоненциальную функцию,
// реализовав линейный алгоритм
int64_t T(int i) {
/*     if (i <= 1) {
        return 0;
    }
    if (i == 2) {
        return 1;
    }

    return T(i - 1) + T(i - 2) + T(i - 3);

     if (i == 0) {
        return 0;
    } */

    int64_t prev0 = 0, prev1 = 0, prev2 = 1;

    for (int t = 1; t < i; ++t) {
        int64_t next = prev0 + prev1 + prev2;
        prev0 = prev1;
        prev1 = prev2;
        prev2 = next;
    }

    return prev1;
}

int main() {
    int i;

    while (true) {
        cout << "Enter index: "s;
        if (!(cin >> i)) {
            break;
        }

        cout << "Ti = "s << T(i) << endl;
    }
}