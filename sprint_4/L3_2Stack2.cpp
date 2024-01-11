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
class StackMin {
   public:
    void Push(const Type& element) {
        if (elements_.IsEmpty()) {
            min_val.push_back(element);
        } else {
            min_val.back() < element ? min_val.push_back(min_val.back()) : min_val.push_back(element);
        }
        elements_.Push(element);
    }
    void Pop() {
        elements_.Pop();
        min_val.pop_back();
    }
    const Type& Peek() const {
        return elements_.Peek();
    }
    Type& Peek() {
        return elements_.Peek();
    }
    void Print() const {
        // работу этого метода мы проверять не будем,
        // но если он вам нужен, то можете его реализовать

        elements_.Print();
    }
    uint64_t Size() const {
        return elements_.size();
    }
    bool IsEmpty() const {
        return elements_.IsEmpty();
    }
    const Type& PeekMin() const {
        return min_val.back();
    }
    Type& PeekMin() {
        return min_val.back();
        // напишите реализацию метода
    }

   private:
    Stack<Type> elements_;
    vector<Type> min_val;

    // возможно, здесь вам понадобится что-то изменить
};

int main() {
    StackMin<int> stack;
    vector<int> values(5);
    // заполняем вектор для тестирования нашего стека
    iota(values.begin(), values.end(), 1);
    // перемешиваем значения
    random_device rd;
    mt19937 g(rd());
    shuffle(values.begin(), values.end(), g);
    // заполняем стек
    for (int i = 0; i < 5; ++i) {
        stack.Push(values[i]);
    }
    // печатаем стек и его минимум, постепенно убирая из стека элементы
    while (!stack.IsEmpty()) {
        stack.Print();
        cout << "Минимум = "s << stack.PeekMin() << endl;
        stack.Pop();
    }
}