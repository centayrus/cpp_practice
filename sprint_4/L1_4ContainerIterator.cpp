#include <iostream>
#include <set>
#include <vector>

using namespace std;

template <typename Container>
void PrintRange(Container container1, Container container2) {
    for (; container1 != container2; ++container1) {
        cout << *container1 << " "s;
    }
    cout << endl;
}

template <typename Container>
auto MakeVector(Container first, Container last) {
    return vector(first, last);
}

int main() {
    set<string> unique_langs = {"Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s};
    vector<string> langs = MakeVector(unique_langs.begin(), unique_langs.end());
    PrintRange(langs.begin(), langs.end());
}