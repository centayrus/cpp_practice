#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
void ReverseArray(T *start, size_t size) {

    T temp;
    if (size > 1 && size % 2 == 0)
        for (std::size_t i = 0, j = size - 1; j > i; ++i, --j) {
            temp = start[j];
            start[j] = start[i];
            start[i] = temp;
        }
    else if (size > 1 && size % 2 == 1) {
        for (std::size_t i = 0, j = size - 1; j > i; ++i, --j) {
            temp = start[j];
            start[j] = start[i];
            start[i] = temp;
            if ((j - i) == 1) {
                return;
            }
        }
    } else {
        return;
    }
}

int main() {
    using namespace std;

    vector<int> v = {1, 2, 3};
    ReverseArray(v.data(), v.size());
    assert(v == (vector<int>{3, 2, 1}));
}