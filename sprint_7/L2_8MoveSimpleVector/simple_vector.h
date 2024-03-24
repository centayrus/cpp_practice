// вставьте сюда ваш код для класса SimpleVector
// внесите необходимые изменения для поддержки move-семантики#pragma once

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <utility>

#include "array_ptr.h"

// класс-обертка
class ReserveProxyObj {
public:
    explicit ReserveProxyObj(size_t capacity_to_reserve)
        : capacity_(capacity_to_reserve) {
    }

    auto GetObjCapacity() {
        return capacity_;
    }

private:
    size_t capacity_;
};

ReserveProxyObj Reserve(size_t capacity_to_reserve) {
    return ReserveProxyObj(capacity_to_reserve);
}

template <typename Type>
class SimpleVector {
public:
    using Iterator = Type *;
    using ConstIterator = const Type *;

    SimpleVector() noexcept = default;

    // SimpleVector(const SimpleVector &other) = default;
    // SimpleVector operator=(const SimpleVector &other) = default;

    // SimpleVector(SimpleVector &&other) = default;
    // SimpleVector &operator=(SimpleVector &&other) = default;

    // Конструктор копирования
    SimpleVector(const SimpleVector &other) {
        SimpleVector<Type> u(other.GetSize());
        std::copy(other.begin(), other.end(), u.begin());
        items_.swap(u.items_);
        this->capacity_ = other.GetCapacity();
        this->size_ = other.GetSize();
    }

    SimpleVector(SimpleVector &&other) {
        items_ = std::move(other.items_);
        size_ = std::exchange(other.size_, 0);
        capacity_ = std::exchange(other.capacity_, 0);
    }

    // Создаёт вектор из size элементов, инициализированных значением по умолчанию
    explicit SimpleVector(size_t size) : items_(size), size_(size), capacity_(size) {
        size_ = size;
        capacity_ = size;
        if (size > 0) {
            std::fill(items_.Get(), items_.Get() + size_, 0);
        }
    }

    // Создаёт вектор из size элементов, инициализированных значением value
    SimpleVector(size_t size, const Type &value) : items_(size), size_(size), capacity_(size) {
        std::fill(items_.Get(), items_.Get() + size_, value);
    }

    // Создаёт вектор из size элементов, инициализированных значением value
    SimpleVector(size_t size, Type &&value) : items_(size), size_(size), capacity_(size) {
        for (size_t i = 0; i < size_; ++i) {
            items_[i] = std::move(value);
        }
    }

    // Создаёт вектор из std::initializer_list
    SimpleVector(std::initializer_list<Type> init) : items_(init.size()) {
        size_ = init.size();
        capacity_ = init.size();

        if (init.size() > 0) {
            size_t i = 0;
            for (const Type e : init) {
                items_[i] = e;
                ++i;
            }
        }
    }

    SimpleVector(ReserveProxyObj rpo) : capacity_(rpo.GetObjCapacity()) {
    }

    // Возвращает количество элементов в массиве
    size_t GetSize() const noexcept {
        return size_;
    }

    // Возвращает вместимость массива
    size_t GetCapacity() const noexcept {
        return capacity_;
    }

    // Сообщает, пустой ли массив
    bool IsEmpty() const noexcept {
        if (size_ == 0) {
            return true;
        }
        return false;
    }

    // Возвращает ссылку на элемент с индексом index
    Type &operator[](size_t index) noexcept {
        return items_[index];
    }

    // Возвращает константную ссылку на элемент с индексом index
    const Type &operator[](size_t index) const noexcept {
        return items_[index];
    }

    // Возвращает константную ссылку на элемент с индексом index
    // Выбрасывает исключение std::out_of_range, если index >= size
    Type &At(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("");
        }
        return items_[index];
    }

    // Возвращает константную ссылку на элемент с индексом index
    // Выбрасывает исключение std::out_of_range, если index >= size
    const Type &At(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("");
        }
        return items_[index];
    }

    // Обнуляет размер массива, не изменяя его вместимость
    void Clear() noexcept {
        size_ = 0;
    }

    // Изменяет размер массива.
    // При увеличении размера новые элементы получают значение по умолчанию для типа Type
    void Resize(size_t new_size) {
        if (new_size <= size_) {
            size_ = std::move(new_size);
        } else if (new_size <= capacity_) {
            //std::fill(items_.Get() + size_, items_.Get() + new_size, 0);
            for (size_t i = size_; i < new_size; ++i)
        {
            items_[i] = std::move(Type());
        }
            size_ = std::move(new_size);
        } else if (new_size > capacity_) {
            SimpleVector<Type> u(std::move(new_size));
            std::copy(std::make_move_iterator(items_.Get()), std::make_move_iterator(items_.Get()) + size_, u.items_.Get());
            //std::fill(u.items_.Get() + size_, u.items_.Get() + new_size, 0);
            for (size_t i = size_; i < new_size; ++i)
        {
            u[i] = std::move(Type());
        }
            //this->items_.swap(u.items_);
            items_ = std::move(u.items_);
            size_ = std::move(new_size);
            capacity_ = std::move(new_size);
        }
    }

    // Возвращает итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    Iterator begin() noexcept {
        return items_.Get();
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    Iterator end() noexcept {
        return items_.Get() + size_;
    }

    // Возвращает константный итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator begin() const noexcept {
        return items_.Get();
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator end() const noexcept {
        return items_.Get() + size_;
    }

    // Возвращает константный итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator cbegin() const noexcept {
        return items_.Get();
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator cend() const noexcept {
        return items_.Get() + size_;
    }

    SimpleVector &operator=(const SimpleVector &rhs) {
        SimpleVector<Type> u(rhs);
        items_.swap(u.items_);
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        return *this;
    }

    SimpleVector &operator=(SimpleVector &&rhs) {
        if (this == &rhs) {
            return *this;
        }
        items_ = std::move(rhs.items_);
        size_ = std::exchange(rhs.size_, 0);
        capacity_ = std::exchange(rhs.capacity_, 0);
        return *this;
    }

    

    // Добавляет элемент в конец вектора
    // При нехватке места увеличивает вдвое вместимость вектора
    void PushBack(const Type &item) {
        if (capacity_ == 0) {
            SimpleVector<Type> u(1);
            std::copy(begin(), end(), u.begin());
            u[size_] = item;
            ++size_;
            ++capacity_;
            items_.swap(u.items_);
        } else if (size_ < capacity_) {
            *this->end() = item;
            ++size_;
        } else {
            SimpleVector<Type> u(2 * capacity_);
            std::copy(begin(), end(), u.begin());
            u[size_] = item;
            ++size_;
            capacity_ *= 2;
            items_.swap(u.items_);
        }
    }

        void PushBack(Type &&item) {
        if (capacity_ == 0) {
            SimpleVector<Type> u(1);
            std::copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), u.begin());
            u[size_] = std::move(item);
            ++size_;
            ++capacity_;
            items_.swap(u.items_);
        } else if (size_ < capacity_) {
            *this->end() = std::move(item);
            ++size_;
        } else {
            SimpleVector<Type> u(2 * capacity_);
            std::copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), u.begin());
            u[size_] = std::move(item);
            ++size_;
            capacity_ *= 2;
            items_.swap(u.items_);
        }
    }

    // Вставляет значение value в позицию pos.
    // Возвращает итератор на вставленное значение
    // Если перед вставкой значения вектор был заполнен полностью,
    // вместимость вектора должна увеличиться вдвое, а для вектора вместимостью 0 стать равной 1
    Iterator Insert(ConstIterator pos, const Type &value) {
        auto p = const_cast<Type *>(pos);
        if (capacity_ == 0) {
            SimpleVector<Type> u(0);
            u.PushBack(value);
            items_.swap(u.items_);
            size_ = u.GetSize();
            capacity_ = u.GetCapacity();
            p = end() - 1;
        } else if (size_ == 0) {
            PushBack(value);
        } else if (size_ > 0 && size_ < capacity_) {
            std::copy_backward(p, end(), end() + 1);
            *p = value;
            ++size_;
        } else if (size_ == capacity_) {
            SimpleVector<Type> u(2 * capacity_);
            u.size_ = size_;
            std::copy(begin(), p, u.begin());
            std::copy_backward(p, end(), u.end() + 1);
            auto n = std::distance(begin(), p);
            u[n] = value;
            items_.swap(u.items_);
            ++size_;
            capacity_ = u.capacity_;
            p = begin() + n;
        }
        return p;
    }

    Iterator Insert(ConstIterator pos, Type &&value) {
        auto p = const_cast<Type *>(pos);
        if (capacity_ == 0) {
            SimpleVector<Type> u(0);
            u.PushBack(std::move(value));
            items_.swap(u.items_);
            size_ = std::move(u.GetSize());
            capacity_ = std::move(u.GetCapacity());
            p = end() - 1;
        } else if (size_ == 0) {
            PushBack(std::move(value));
        } else if (size_ > 0 && size_ < capacity_) {
            std::copy_backward(std::make_move_iterator(p), std::make_move_iterator(end()), end() + 1);
            *p = std::move(value);
            ++size_;
        } else if (size_ == capacity_) {
            SimpleVector<Type> u(2 * capacity_);
            u.size_ = size_;
            std::copy(std::make_move_iterator(begin()), std::make_move_iterator(p), u.begin());
            std::copy_backward(std::make_move_iterator(p), std::make_move_iterator(end()), u.end() + 1);
            auto n = std::distance(begin(), p);
            u[n] = std::move(value);
            items_.swap(u.items_);
            ++size_;
            capacity_ = std::move(u.capacity_);
            p = std::move( begin() + n);
        }
        return p;
    }

    // "Удаляет" последний элемент вектора. Вектор не должен быть пустым
    void PopBack() noexcept {
        --this->size_;
    }

    // Удаляет элемент вектора в указанной позиции
    Iterator Erase(ConstIterator pos) {
        auto p = std::move(const_cast<Type *>(pos));
        if (size_ > 0) {
            std::copy(std::make_move_iterator(p)+1, std::make_move_iterator(end()), p);
            --size_;
        }
        return p;
}                                   

    // Обменивает значение с другим вектором
    void swap(SimpleVector &other) noexcept {
        items_.swap(other.items_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity > GetCapacity()) {
            SimpleVector<Type> u(new_capacity);
            std::copy(begin(), end(), u.begin());
            items_.swap(u.items_);
            capacity_ = new_capacity;
        }
    }

private:
    ArrayPtr<Type> items_;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

template <typename Type>
inline bool operator==(const SimpleVector<Type> &lhs, const SimpleVector<Type> &rhs) {
    return !(lhs < rhs) || !(rhs < lhs);
}

template <typename Type>
inline bool operator!=(const SimpleVector<Type> &lhs, const SimpleVector<Type> &rhs) {
    return (lhs < rhs) || (rhs < lhs);
}

template <typename Type>
inline bool operator<(const SimpleVector<Type> &lhs, const SimpleVector<Type> &rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
inline bool operator<=(const SimpleVector<Type> &lhs, const SimpleVector<Type> &rhs) {
    return !(lhs > rhs);
}

template <typename Type>
inline bool operator>(const SimpleVector<Type> &lhs, const SimpleVector<Type> &rhs) {
    return rhs < lhs;
}

template <typename Type>
inline bool operator>=(const SimpleVector<Type> &lhs, const SimpleVector<Type> &rhs) {
    return !(lhs < rhs);
}
