#include <iostream>


using namespace std;


int main() {
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
                        cout << result << endl;
                        
                    }
                }
            }
        }
    }



    return 0;
}
