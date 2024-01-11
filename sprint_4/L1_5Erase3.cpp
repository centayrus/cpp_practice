#include <iostream>
#include <set>
#include <vector>

using namespace std;

template <typename Container>
void PrintRange(Container range_begin, Container range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename Container>
auto MakeVector(Container first, Container last) {
    return vector(first, last);
}

template <typename Container>
void EraseAndPrint(Container& container, int it, int begin, int end) {
    /* auto it_to_erased =  */ container.erase(container.begin() + it);
    PrintRange(container.begin(), container.end());
    container.erase(container.begin() + begin, container.begin() + end);
    PrintRange(container.begin(), container.end());
}

int main() {
    vector<string> langs = {"Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s};
    EraseAndPrint(langs, 0, 0, 2);
    return 0;
}

// numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [](int n) { return n % 2 == 0; }), numbers.end());