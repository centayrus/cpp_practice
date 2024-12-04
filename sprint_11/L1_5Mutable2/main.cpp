#include <cassert>
#include <functional>
#include <optional>
#include <string>

using namespace std;

template <typename T>
class LazyValue {
public:
    explicit LazyValue(function<T()> init)
        : initializer_(move(init)), value_() {};

    bool HasValue() const {
        return value_.has_value();
    }
    const T &Get() const {
        if (!value_) {
            value_ = initializer_();
        }
        return *value_;
    }

private:
    function<T()> initializer_;
    mutable optional<T> value_;

};

void UseExample() {
    const string big_string = "Giant amounts of memory"s;

    LazyValue<string> lazy_string([&big_string] {
        return big_string;
    });

    assert(!lazy_string.HasValue());
    assert(lazy_string.Get() == big_string);
    assert(lazy_string.Get() == big_string);
}

void TestInitializerIsntCalled() {
    bool called = false;

    {
        LazyValue<int> lazy_int([&called] {
            called = true;
            return 0;
        });
    }
    assert(!called);
}

int main() {
    UseExample();
    TestInitializerIsntCalled();
}