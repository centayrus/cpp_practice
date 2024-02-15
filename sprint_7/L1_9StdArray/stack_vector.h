#pragma once

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
        size_ = a_size;
    };

    T &operator[](size_t index) {
        return vector_stack_[index];
    }

    const T &operator[](size_t index) const {
        return vector_stack_[index];
    }

    typename std::array<T, N>::iterator begin() {
        return vector_stack_.begin();
    }
    typename std::array<T, N>::iterator end() {
        return vector_stack_.begin() + size_;
    }
    typename std::array<T, N>::const_iterator begin() const {
        return vector_stack_.begin();
    }
    typename std::array<T, N>::const_iterator end() const {
        return vector_stack_.cbegin() + size_;
    }

    size_t Size() const {
        return size_;
    }
    size_t Capacity() const {
        return vector_stack_.max_size();
    }

    void PushBack(const T &value) {
        using namespace std::literals;
        if (vector_stack_.max_size() == size_) {
            throw std::overflow_error("vector size is equal capacity"s);
        }
        vector_stack_[size_] = value;
        ++size_;
    }

    T PopBack() {
        using namespace std::literals;
        if (size_ == 0) {
            throw std::underflow_error("vector size is null"s);
        }
        --size_;
        return vector_stack_[size_];
    }

private:
    size_t size_;
    std::array<T, N> vector_stack_;
};
