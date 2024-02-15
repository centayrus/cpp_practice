#pragma once

#include <cassert>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

#include "array_ptr.h"

template <typename Type>
class SimpleVector {
public:
    using Iterator = Type *;
    using ConstIterator = const Type *;

    SimpleVector() noexcept = default;

    // Создаёт вектор из size элементов, инициализированных значением по умолчанию
    explicit SimpleVector(size_t size) : items_(size) {
        size_ = size;
        capacity_ = size;
        
        if (size > 0) {
            std::fill(items_.Get(), items_.Get() + size_, 0);
        }
    }

    // Создаёт вектор из size элементов, инициализированных значением value
    SimpleVector(size_t size, const Type &value) : items_(size) {
        size_ = size;
        capacity_ = size;
       // ArrayPtr<Type> items_(size); 
        if (size > 0) {
            std::fill(items_.Get(), items_.Get() + size_, value);
        }
    }

    // Создаёт вектор из std::initializer_list
     SimpleVector(std::initializer_list<Type> init) :items_(init.size()) {
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
            size_ = new_size;
        } else if (new_size <= capacity_) {
            std::fill(items_.Get() + size_, items_.Get() + new_size, 0);
            size_ = new_size;
        } else if (new_size > capacity_) {
            SimpleVector<Type> u(new_size);
            std::copy(items_.Get(), items_.Get()+size_, u.items_.Get());
            std::fill(u.items_.Get()+size_, u.items_.Get()+new_size, 0);
            this->items_.swap(u.items_);
            size_ = new_size;
            capacity_ = new_size;
        }
    }

    // // Возвращает итератор на начало массива
    // // Для пустого массива может быть равен (или не равен) nullptr
    // Iterator begin() noexcept {
    //     return items_.Get();
    // }

    // // Возвращает итератор на элемент, следующий за последним
    // // Для пустого массива может быть равен (или не равен) nullptr
    // Iterator end() noexcept {
    //     return items_.Get() + size_;
    // }

    // // Возвращает константный итератор на начало массива
    // // Для пустого массива может быть равен (или не равен) nullptr
    // ConstIterator begin() const noexcept {
    //     return items_.Get();
    // }

    // // Возвращает итератор на элемент, следующий за последним
    // // Для пустого массива может быть равен (или не равен) nullptr
    // ConstIterator end() const noexcept {
    //     return items_.Get() + size_;
    // }

    // // Возвращает константный итератор на начало массива
    // // Для пустого массива может быть равен (или не равен) nullptr
    // ConstIterator cbegin() const noexcept {
    //     return items_.Get();
    // }

    // // Возвращает итератор на элемент, следующий за последним
    // // Для пустого массива может быть равен (или не равен) nullptr
    // ConstIterator cend() const noexcept {
    //     return items_.Get() + size_;
    // }

private:
    ArrayPtr<Type> items_;
    size_t size_ = 0;
    size_t capacity_ = 0;
};
