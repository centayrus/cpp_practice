#include <iostream>
#include <set>
#include <vector>

using namespace std;

template <typename Container>
void PrintRange( Container container1, Container container2) {
    for ( ; container1 != container2; ++container1) {
        cout << *container1 << " "s;
    }
    cout << endl;
}

int main() {
    cout << "Test1"s << endl;
    set<int> test1 = {1, 1, 1, 2, 3, 4, 5, 5};
    PrintRange(test1.begin(), test1.end());
    cout << "Test2"s << endl;
    vector<int> test2 = {}; // пустой контейнер
    PrintRange(test2.begin(), test2.end());
    cout << "End of tests"s << endl;
} 