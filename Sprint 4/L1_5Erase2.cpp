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
void EraseAndPrint(Container& container, int it) {
    auto it_to_erased = container.erase(container.begin()+it);
    PrintRange(container.begin(), it_to_erased);
    PrintRange(it_to_erased, container.end());
}


int main() {
   // set<string> langs = {"Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s};
   // EraseAndPrint(langs, langs.begin());

    vector<string> langss = {"Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s};
    EraseAndPrint(langss, 2);
    return 0;
}

// numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [](int n) { return n % 2 == 0; }), numbers.end());