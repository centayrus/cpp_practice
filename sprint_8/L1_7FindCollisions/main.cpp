#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename Hash>
int FindCollisions(const Hash &hasher, istream &text) {

    string word;
    unordered_map<size_t, unordered_set<string>> search_base;
    size_t h;
    int counter = 0;
    while (text >> word) {
        h = hasher(word);
        if (search_base.count(h) == 1 && search_base.at(h).count(word) != 1) {
            ++counter;
        }
        search_base[h].insert(move(word));
    }
    return counter;
}

// Это плохой хешер. Его можно использовать для тестирования.
// Подумайте, в чём его недостаток
struct HasherDummy {
    size_t operator()(const string &str) const {
        size_t res = 0;
        for (char c : str) {
            res += static_cast<size_t>(c);
        }
        return res;
    }
};

int main() {
    hash<string> str_hasher;
    int collisions = FindCollisions(str_hasher, cin);
    cout << "Found collisions: "s << collisions << endl;
}
