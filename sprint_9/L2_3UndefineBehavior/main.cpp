#include <climits>
#include <cstdint>
#include <iostream>

using namespace std;

int main() {
    int64_t a ;//= 4567890123456789012;
    int64_t b;// = 5678901234567890123;
     cin >> a >> b;
 //   cout << LLONG_MIN << endl;
    if (a < 0 && b < 0) {
        if (a < LLONG_MIN - b) {
            cout << "Overflow!"s << endl;
        } else {
            cout << a + b << endl;
        }
    } else if ((a > 0 && b > 0)) {
        if (a > LLONG_MAX - b) {
            cout << "Overflow!"s << endl;
        } else {
            cout << a + b << endl;
        }
    } else {
        cout << a + b << endl;
    }
}
