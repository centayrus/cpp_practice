#include <iostream>

using namespace std;

bool IsPowOfTwo(int number) {
    bool res = false;
    if (number == 1) {
        return true;
    }
    if (number == 0) {
        return false;
    }
    if (number % 2 == 0 || number > 1) {
        IsPowOfTwo(number / 2);
    }
    return res;
}

int main() {
    int result = IsPowOfTwo(1);
    cout << result << endl;
}
 