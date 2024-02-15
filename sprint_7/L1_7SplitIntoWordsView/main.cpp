#include <cassert>
#include <iostream>
#include <string_view>
#include <vector>

using namespace std;

vector<string_view> SplitIntoWordsView(string_view str) {
    vector<string_view> result;
    //int64_t pos = str.find_first_not_of(" ");
    str.remove_prefix(std::min(str.find_first_not_of(" "), str.size()));
    //const int64_t pos_end = str.npos;
    
    while (str.size() > 0) {
        int64_t space = str.find(' ');
       // result.push_back(space == str.npos ? str.substr(0, pos_end) : str.substr(0, space));

       result.push_back(str.substr(0, space));
        //pos = str.find_first_not_of(" ", space);
        str.remove_prefix(std::min(str.find_first_not_of(" "), str.size()));
    }

    return result;
}

int main() {
    assert((SplitIntoWordsView("") == vector<string_view>{}));
    assert((SplitIntoWordsView("     ") == vector<string_view>{}));
  // assert((SplitIntoWordsView("aaaaaaa") == vector{"aaaaaaa"sv}));
    assert((SplitIntoWordsView("a") == vector{"a"sv}));
    assert((SplitIntoWordsView("a b c") == vector{"a"sv, "b"sv, "c"sv}));
    assert((SplitIntoWordsView("a    bbb   cc") == vector{"a"sv, "bbb"sv, "cc"sv}));
    assert((SplitIntoWordsView("  a    bbb   cc") == vector{"a"sv, "bbb"sv, "cc"sv}));
    assert((SplitIntoWordsView("a    bbb   cc   ") == vector{"a"sv, "bbb"sv, "cc"sv}));
    assert((SplitIntoWordsView("  a    bbb   cc   ") == vector{"a"sv, "bbb"sv, "cc"sv}));
    cout << "All OK" << endl;
}