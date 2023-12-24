#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <vector>

using namespace std;

template <typename Container>
void PrintRange(Container range_begin, Container range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    int lenth = (range_end - range_begin) / 2;
    if (lenth > 0) {
        MergeSort(range_begin, range_begin + lenth);
        MergeSort(range_begin + lenth, range_end);
        std::inplace_merge(range_begin, range_begin + lenth, range_end);
    }
}

int main() {
    vector<int> test_vector(100);
    // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
    // Заполняет диапазон последовательно возрастающими значениями
    iota(test_vector.begin(), test_vector.end(), 1);

    // shuffle   -> https://ru.cppreference.com/w/cpp/algorithm/random_shuffle
    // Перемешивает элементы в случайном порядке
    random_device rd;
    mt19937 g(rd());
    shuffle(test_vector.begin(), test_vector.end(), g);

    // Выводим вектор до сортировки
    PrintRange(test_vector.begin(), test_vector.end());
    // Сортируем вектор с помощью сортировки слиянием
    MergeSort(test_vector.begin(), test_vector.end());
    // Выводим результат
    PrintRange(test_vector.begin(), test_vector.end());
    return 0;
}