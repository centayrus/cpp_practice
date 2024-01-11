#include <algorithm>
#include <iostream>
#include <numbers>
#include <random>
#include <stdint.h>
#include <vector>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename Type>
class Stack {
   public:
    void Push(const Type& element) {
        elements_.push_back(element);
    }
    void Pop() {
        elements_.pop_back();
    }
    const Type& Peek() const {
            return elements_.back();
    }
    Type& Peek() {
        return elements_.back();
    }
    void Print() const {
        for (auto i : elements_) {
            cout << i << " "s;
        }
        cout << endl;
    }
    uint64_t Size() const {
        return elements_.size();
    }
    bool IsEmpty() const {
        return elements_.empty();
    }

   private:
    vector<Type> elements_;
};

template <typename Type>
class SortedSack {
   public:
    void Push(const Type& element) {
        Type tmp_elem;
        if (elements_.IsEmpty() || element <= elements_.Peek()) {
            elements_.Push(element);
        } else {
        tmp_elem = elements_.Peek();
        elements_.Pop();
        Push(element);
        elements_.Push(tmp_elem);
        }
        
    }
    void Pop() {
        elements_.Pop();
    }
    const Type& Peek() const {
        return elements_.Peek();
    }
    Type& Peek() {
        return elements_.Peek();
    }
    void Print() const {
        elements_.Print();
    }
    uint64_t Size() const {
        return elements_.Size();
    }
    bool IsEmpty() const {
        return elements_.IsEmpty();
    }

   private:
    Stack<Type> elements_;
};

int main() {
    SortedSack<int> sack;
    vector<int> values(5);
    // заполняем вектор для тестирования нашего класса
    iota(values.begin(), values.end(), 1);
    // перемешиваем значения
    random_device rd;
    mt19937 g(rd());
    shuffle(values.begin(), values.end(), g);

    // заполняем класс и проверяем, что сортировка сохраняется после каждой вставки
    for (int i = 0; i < 5; ++i) {
        cout << "Вставляемый элемент = "s << values[i] << endl;
        sack.Push(values[i]);
        sack.Print();
    }
}