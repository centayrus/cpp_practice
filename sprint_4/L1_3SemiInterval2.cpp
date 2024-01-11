#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

template <typename Container, typename ContainerItem>
void FindAndPrint(const Container& container, const ContainerItem& elem) {
    auto str = find(container.begin(), container.end(), elem);
    auto first = container.begin();
    auto last = container.end();
    bool is_befor = true;
    for (; first != last; first++) {
        if (str == last)  {
            for (const auto& s : container) {
            cout << s << " "s;
            }
            cout << endl;
            break;
        }
        if (str != first && is_befor) {
            cout << *first << " "s;

        } else if (str == first) {
            cout << endl;
            cout << *first << " "s;
            is_befor = false;
        } else {
            cout << *first << " "s;
        }
    

    }
    cout << endl;
}

int main() {
    set<int> test = {1, 1, 1, 2, 3, 4, 5, 5};
    cout << "Test1"s << endl;
    FindAndPrint(test, 3);
    cout << "Test2"s << endl;
    FindAndPrint(test, 0);  // элемента 0 нет в контейнере
    cout << "End of tests"s << endl;
}

/*
//примсмотрись сюда
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    int n1 = 3;
    int n2 = 5;

    std::vector<int> v{0, 1, 2, 3, 4};

    auto result1 = std::find(v.begin(), v.end(), n1);
    auto result2 = std::find(v.begin(), v.end(), n2);

    if (result1 != v.end()) {
        std::cout << "v содержит: " << n1 << '\n';
    } else {
        std::cout << "v не содержит: " << n1 << '\n';
    }

    if (result2 != v.end()) {
        std::cout << "v содержит: " << n2 << '\n';
    } else {
        std::cout << "v не содержит: " << n2 << '\n';
    }
}

Test1
1 2
3 4 5
Test2
1 2 3 4 5

End of tests
 */