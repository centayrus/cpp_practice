#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;

// функция, записывающая элементы диапазона в строку
template <typename It>
string PrintRangeToString(It range_begin, It range_end) {
    // удобный тип ostringstream -> https://ru.cppreference.com/w/cpp/io/basic_ostringstream
    ostringstream out;
    for (auto it = range_begin; it != range_end; ++it) {
        out << *it << " "s;
    }
    out << endl;
    // получаем доступ к строке с помощью метода str для ostringstream
    return out.str();
}

template <typename It>
auto GetPermutations(It start, It stop) {
    vector<int> int_v = {start, stop};
    sort(int_v.begin(), int_v.end());
   // string str;
       vector<string> str_v;
    do {
        str_v.push_back(PrintRangeToString(int_v.begin(), int_v.end()));

    } while (std::next_permutation(int_v.begin(), int_v.end()) );

    return str_v;
}

int main() {
    vector<int> permutation;
    // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
    // Заполняет диапазон последовательно возрастающими значениями
    //iota(permutation.begin(), permutation.end(), 1);
    permutation = {3,1,2};
    auto result = GetPermutations(permutation.begin(), permutation.end());

    cout << PrintRangeToString(result.begin(), result.end());
    for (const auto& s : result) {
       cout << s;
    }
    return 0;
}