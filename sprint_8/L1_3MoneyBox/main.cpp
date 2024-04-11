#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class MoneyBox {
public:
    void PushCoin(int value) {
        assert(value >= 0 && value <= 10);
        ++counts_[value];
    }

    void PrintCoins(ostream& out) const {
        for (size_t i = 0; i < counts_.size(); ++i) {
            if (counts_[i] > 0) {
                out << i << ": "s << counts_[i] << endl;
            }
        }
    }

private:
    // создаём вектор размера 5001 для того, чтобы последний
    // индекс соответствовал максимальному номиналу 5000
    vector<int> counts_ = vector<int>(10);
};

ostream& operator<<(ostream& out, const MoneyBox& cash) {
    cash.PrintCoins(out);
    return out;
}

int main() {
    MoneyBox cash;

    int value;
    while (cin >> value) {
        cash.PushCoin(value);
    }

    cout << cash << endl;
}