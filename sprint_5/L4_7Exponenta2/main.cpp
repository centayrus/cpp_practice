#include <iostream>
#include <string>

using namespace std;

template <typename F>
string BruteForce(F check) {
    string result("A", 5);
    for (auto chr = 'A'; chr <= 'Z'; ++chr) {
        result[0] = chr;
        for (auto chr = 'A'; chr <= 'Z'; ++chr) {
            result[1] = chr;
            for (auto chr = 'A'; chr <= 'Z'; ++chr) {
                result[2] = chr;
                for (auto chr = 'A'; chr <= 'Z'; ++chr) {
                    result[3] = chr;
                    for (auto chr = 'A'; chr <= 'Z'; ++chr) {
                        result[4] = chr;
                        if (check(result)) {
                            return result;
                        }
                    }
                }
            }
        }
    }
    return "Пароль не найден"s;
}

int main() {
    string pass = "ARTUR"s;
    auto check = [pass](const string &s) {
        return s == pass;
    };
    cout << BruteForce(check) << endl;
}