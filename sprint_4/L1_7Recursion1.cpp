// #include <string>
#include <iostream>

using namespace std;

unsigned int Fibonacci(unsigned int iter) {
    if (iter == 1 || iter == 2)
        return 1;
    if (iter == 0)
        return 0;
    return Fibonacci(iter - 1) + Fibonacci(iter - 2);
}

int main() {
    cout << Fibonacci(45) << endl;
}