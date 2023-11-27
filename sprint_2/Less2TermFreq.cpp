#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

map<string, int> ComputeTermFreqs(const vector<string>& terms) {
    // реализуйте функцию
    //set<string> terms_set = s(terms.begin(), terms.end());
    map<string, int> return_value;
   // double count = 1.0 / static_cast<double>(terms.size());
    //set<string> terms_set(terms.begin(), terms.end());
    for (const auto &str : terms) {
       ++return_value[str];
    }
    return return_value;

}

int main() {
    const vector<string> terms = {"first"s, "time"s, "first"s, "class"s};
    for (const auto& [term, freq] : ComputeTermFreqs(terms)) {
        cout << term << " x "s << freq << endl;
    }
    // вывод:
    // class x 1
    // first x 2
    // time x 1
}