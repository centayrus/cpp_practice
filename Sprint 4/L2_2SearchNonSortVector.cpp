#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void PrintSpacesPositions(string& str) {
    for (auto i = str.begin(); i != str.end();) {
        auto i2 = find(i, str.end(), ' ');
        if (i2 == str.end()) {
            i = i2;
            continue;
        }
        cout << distance(str.begin(), i2) << " "s;
        i = next(i2);
    }
}

int main() {
    string str = "He said: one and one and one is three"s;
    PrintSpacesPositions(str);
    return 0;
}