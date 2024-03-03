#include <array>
#include <stdexcept>
#include <string>

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0)  { 
        using namespace std::literals;
        if (a_size > N) {
            throw std::invalid_argument("Size exceed Capacity"s);
        }
     //   vector_stack_.fill(a_size);
    };

    T &operator[](size_t index) {
        
        return vector_stack_[index];
    }

    const T &operator[](size_t index) const {
        return vector_stack_[index];
    }

    auto begin() {
        vector_stack_.begin();
    }
    auto end() {
        vector_stack_.end();
    }
    auto begin() const {
        vector_stack_.cbegin();
    }
    auto end() const {
        vector_stack_.cend();
    }

    size_t Size() const {
        return vector_stack_.size();
    }
    size_t Capacity() const {
        return vector_stack_.max_size();
    }

    void PushBack(const T &value) {
        using namespace std::literals;
        if (vector_stack_.size() == vector_stack_.max_size()) {
            throw std::overflow_error("vector size is equal capacity"s);
        }
        vector_stack_.fill(value);
    }

    T PopBack() {
        using namespace std::literals;
        if (vector_stack_.size() == 0) {
            throw std::underflow_error("vector size is null"s);
        }
        auto elem = vector_stack_.back();

        return elem;
    }

private:
    std::array<T, N> vector_stack_;
};
