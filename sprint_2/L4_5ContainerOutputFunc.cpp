#include <iostream>
#include <set>
#include <vector>
#include <map>

using namespace std;
template <typename Mkey, typename Mval>
ostream& operator<<(ostream& out, const pair<Mkey, Mval>& container) {
    out << "("s;
    out << container.first;
    out << ", "s;
    out << container.second;
    out << ")"s;
    return out;
}

template <typename Container>
ostream& Print(ostream& out, const Container& contain) {
    bool first = true;

    for (const auto& element : contain) {
        if (!first) {
            out << ", "s;
        }
        first = false;
        out << element;
    }

    return out;
}

template <typename Container>
ostream& operator<<(ostream& out, const vector<Container>& container) {
    out << "["s;
    Print(out, container);
    out << "]"s;
    return out;
}

template <typename Container>
ostream& operator<<(ostream& out, const set<Container>& container) {
    out << "{"s;
    Print(out, container);
    out << "}"s;
    return out;
}

template <typename Mkey, typename Mval>
ostream& operator<<(ostream& out, const map<Mkey, Mval>& container) {
    out << "<"s;
    Print(out, container);
    out << ">"s;
    return out;
}

int main() {
const set<string> cats = {"Мурка"s, "Белка"s, "Георгий"s, "Рюрик"s};
cout << cats << endl;
const vector<int> ages = {10, 5, 2, 12};
cout << ages << endl;
const map<string, int> cat_ages = {
    {"Мурка"s, 10}, 
    {"Белка"s, 5},
    {"Георгий"s, 2}, 
    {"Рюрик"s, 12}
};
cout << cat_ages << endl; 
    return 0;
}