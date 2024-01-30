#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <random>

using namespace std;


// функция возвращает true, если векторы из одинаковых элементов
// перепишите эту функцию, улучшив её асимптотическую сложность
bool TestPermut(const vector<int>& v1, const vector<int>& v2) {
    vector<int> v3 = v1;
    vector<int> v4 = v2;
    // если они разной длины, элементы заведомо разные
    if (v1.size() != v2.size()) {
        return false;
    }

    sort(v3.begin(), v3.end());
    sort(v4.begin(), v4.end());

size_t i=0;
    for ( ; i < v1.size(); ++i) {
        if (v3[i] != v4[i]) {
        // проверяем, что каждый элемент первого вектора
        // содержится одинаковое количество раз в обоих векторах
        //if (count(v1.begin(), v1.end(), i) != count(v2.begin(), v2.end(), i)) {
            return false;
        }

    }

    return true;
}

int main() {
    std::mt19937 g;

    int n;
    cin >> n;
    vector<int> v1, v2;
    v1.reserve(n);
    v2.reserve(n);

    for (int i = 0; i < n; ++i) {
        v1.push_back(rand());
        v2.push_back(rand());
    }

    // оба вектора случайны, вряд ли они совпадут
    cout << "Random vectors match? "s << flush;
    cout << (TestPermut(v1, v2) ? "Yes"s : "No"s) << endl;

    // делаем один перестановкой другого явным образом
    v2 = v1;
    shuffle(v2.begin(), v2.end(), g);
    cout << "Permuted vectors match? "s << flush;
    cout << (TestPermut(v1, v2) ? "Yes"s : "No"s) << endl;
}