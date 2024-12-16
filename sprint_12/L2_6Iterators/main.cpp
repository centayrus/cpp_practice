#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <span>
#include <string_view>
#include <vector>

using namespace std;

// Измените сигнатуру этой функции, чтобы она могла
// сливать не только векторы, но и любые другие контейнеры
template <typename InputIt1, typename InputIt2>
// void Merge(const vector<T>& src1, const vector<T>& src2, ostream& out) {
void Merge(InputIt1 src1_first, InputIt1 src1_last, InputIt2 src2_first, InputIt2 src2_last, ostream &out) {
    while (src1_first != src1_last && src2_first != src2_last) {
        if (/* *src1_first < *src2_first */ less<>()(*src1_first, *src2_first)) {
            out << *src1_first++ << endl;
        } else {
            out << *src2_first++ << endl;
        }
    }
    while (src1_first != src1_last) {
        out << *src1_first++ << endl;
    }
    while (src2_first != src2_last) {
        out << *src2_first++ << endl;
    }
}

/* template <typename T>
void MergeSomething(const std::vector<T> &src1, const std::vector<T> &src2, ostream &out) {
    Merge(src1.begin(), src1.end(), src2.begin(), src2.end(), out);
} */

// Реализуйте эти функции. Они должны вызывать ваш вариант функции Merge.
// Чтобы сократить кличество работы, можете реализовать вместо них одну шаблонную.
 template <typename T, typename S>
 void MergeSomething(const T& src1, const S& src2, ostream& out) {
     Merge(src1.begin(), src1.end(), src2.begin(), src2.end(), out);
 } 

/* template <typename T, typename S>
void MergeSomething(const vector<T> &src1, const list<S> &src2, ostream &out) {
    Merge(src1.begin(), src1.end(), src2.begin(), src2.end(), out);
}

template <typename S>
void MergeSomething(const string_view &src1, const list<S> &src2, ostream &out) {
    Merge(src1.begin(), src1.end(), src2.begin(), src2.end(), out);
}

template <typename T, typename S>
void MergeSomething(const set<T> &src1, const vector<S> &src2, ostream &out) {
    Merge(src1.begin(), src1.end(), src2.begin(), src2.end(), out);
} */

// Реализуйте эту функцию:
template <typename T>
void MergeHalves(const vector<T> &src, ostream &out) {
    int mid = (static_cast<int>(src.size()) + 1) / 2;
    // Сделать Merge участка вектора от 0 до mid и от mid до конца.
    // Элемент с индексом mid включается во второй диапазон.
    Merge(src.begin(), std::next(src.begin(),mid), std::next(src.begin(),mid), src.end(), out);

}

int main() {
    vector<int> v1{60, 70, 80, 90};
    vector<int> v2{65, 75, 85, 95};
    vector<int> combined{60, 70, 80, 90, 65, 75, 85, 95};
    list<double> my_list{0.1, 72.5, 82.11, 1e+30};
    string_view my_string = "ACNZ"sv;
    set<unsigned> my_set{20u, 77u, 81u};

    // пока функция MergeSomething реализована пока только для векторов
    cout << "Merging vectors:"sv << endl;
    MergeSomething(v1, v2, cout);

    cout << "Merging vector and list:"sv << endl;
    MergeSomething(v1, my_list, cout);

    cout << "Merging string and list:"sv << endl;
    MergeSomething(my_string, my_list, cout);

    cout << "Merging set and vector:"sv << endl;
    MergeSomething(my_set, v2, cout);

    cout << "Merging vector halves:"sv << endl;
    MergeHalves(combined, cout);
}