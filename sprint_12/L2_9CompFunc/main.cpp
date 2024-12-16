#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <string_view>

using namespace std;

// псевдоним для типа по итератору
template <typename Iterator>
using IterValType = decay_t<decltype(*declval<Iterator>())>;

// псевдоним для компаратора по типу
template <typename T>
using ComparatorByType = bool (const T& x, const T& y);

// псевдоним для компаратора по итератору
template <typename Iterator>
using ComparatorByIterator = ComparatorByType<IterValType<Iterator>>;

template <typename RandomIt>
void SortFuncPtr(RandomIt first, RandomIt last, ComparatorByIterator<RandomIt>* comp) {
    sort(first, last, comp);
}

template <typename T>
void TestComparatorFuncPtr(T comp, std::string_view name) {
    vector v1{3, 1, 4, 555, 3, 4, 6, 3, 345, 53, 5, 345, 3};
    vector v2 = v1;
    
    sort(v1.begin(), v1.end());
    SortFuncPtr(v2.begin(), v2.end(), comp);
    
    cout << "Компаратор "sv << name << ": "sv << (v1 == v2 ? "OK"sv : "Fail"sv) << endl;
}

bool CmpFunctionRef(const int& x, const int& y) {
    return x < y;
}

int main() {
    // осталась только одна возможность
    TestComparatorFuncPtr(CmpFunctionRef, "функция"sv);
}