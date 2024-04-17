#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename Hash>
int FindCollisions(const Hash& hasher, istream& text) {

    string word;
    unordered_map<size_t, unordered_set<string>> search_base;
    size_t h;
    int counter = 0;
    while (text >> word) {
        h = hasher(word);
        if (search_base.count(h) == 1) {
            if (search_base.at(h).count(word) == 1) {
                ++counter;
            } else {
                search_base[h].insert(move(word));
            }
        } else {
            search_base[h].insert(move(word));
        }
        }
        return counter;
    }

struct DummyHash {
    size_t operator()(const string&) const {
        return 42;
    }
};

int main() {
    DummyHash dummy_hash;
    hash<string> good_hash;

    {
        istringstream stream("I love elov C++"s);
        cout << FindCollisions(dummy_hash, stream) << endl;
    }
    {
        istringstream stream("I love C++"s);
        cout << FindCollisions(good_hash, stream) << endl;
    }
}