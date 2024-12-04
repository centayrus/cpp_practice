#include <cassert>
#include <cstddef> // нужно для nullptr_t
#include <utility>

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
public:
    UniquePtr() : value_(nullptr) {}
    explicit UniquePtr(T *ptr) : value_(ptr) {
        ptr = nullptr;
                                 }
    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr(UniquePtr &&other) : value_(other.Get()) {
        other.value_ = nullptr;
    }

    UniquePtr &operator=(nullptr_t) {
        delete value_;
        value_ = nullptr;
        return *this;
    }
    UniquePtr &operator=(UniquePtr &&other) {
        if (this != &other) {
        value_ = other.value_;
        other.value_ = nullptr;
        }
    return *this;    
    }

    ~UniquePtr() {
        delete value_;
    };

    T &operator*() const {
        return *value_;
    }
    T *operator->() const {
        return value_;
    }
    T *Release() {
        auto ptr = value_;
        value_ = nullptr;
        return ptr;
    }
    void Reset(T *ptr) {
        auto old_ptr = value_;
        value_ = ptr;
        if (old_ptr) {
            delete old_ptr;
        } 
    }
    void Swap(UniquePtr &other) {
    
        std::swap(value_, other.value_);
    }

    T *Get() const {
        return value_;
    }
    private:
    T *value_ = nullptr;
};

struct Item {
    static int counter;
    int value;
    Item(int v = 0)
        : value(v) {
        ++counter;
    }
    Item(const Item &other)
        : value(other.value) {
        ++counter;
    }
    ~Item() {
        --counter;
    }
};

int Item::counter = 0;

void TestLifetime() {
    Item::counter = 0;
    {
        UniquePtr<Item> ptr(new Item);
        assert(Item::counter == 1);

        ptr.Reset(new Item);
        assert(Item::counter == 1);
    } 
    assert(Item::counter == 0);

    {
        UniquePtr<Item> ptr(new Item);
        assert(Item::counter == 1);

        auto rawPtr = ptr.Release();
        assert(Item::counter == 1);

        delete rawPtr;
        assert(Item::counter == 0);
    }
    assert(Item::counter == 0);
}

void TestGetters() {
    UniquePtr<Item> ptr(new Item(42));
    assert(ptr.Get()->value == 42);
    assert((*ptr).value == 42);
    assert(ptr->value == 42);
}

int main() {
    TestLifetime();
    TestGetters();
}