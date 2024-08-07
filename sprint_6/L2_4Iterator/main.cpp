#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <iostream>
#include <iterator>

template <typename Type>
class SingleLinkedList {
    // Узел списка
    struct Node {
        Node() = default;
        Node(const Type &val, Node *next)
            : value(val), next_node(next) {
        }
        Type value;
        Node *next_node = nullptr;
    };

    // Шаблон класса «Базовый Итератор».
    // Определяет поведение итератора на элементы односвязного списка
    // ValueType — совпадает с Type (для Iterator) либо с const Type (для ConstIterator)
    template <typename ValueType>
    class BasicIterator {
        // Класс списка объявляется дружественным, чтобы из методов списка
        // был доступ к приватной области итератора
        friend class SingleLinkedList;

        // Конвертирующий конструктор итератора из указателя на узел списка
        explicit BasicIterator(Node *node)
        :node_(node) {
            // assert(false);
            // Реализуйте конструктор самостоятельно
            //node_ = node;
        }

    public:
        // Объявленные ниже типы сообщают стандартной библиотеке о свойствах этого итератора

        // Категория итератора — forward iterator
        // (итератор, который поддерживает операции инкремента и многократное разыменование)
        using iterator_category = std::forward_iterator_tag;
        // Тип элементов, по которым перемещается итератор
        using value_type = Type;
        // Тип, используемый для хранения смещения между итераторами
        using difference_type = std::ptrdiff_t;
        // Тип указателя на итерируемое значение
        using pointer = ValueType *;
        // Тип ссылки на итерируемое значение
        using reference = ValueType &;

        BasicIterator() = default;

        // Конвертирующий конструктор/конструктор копирования
        // При ValueType, совпадающем с Type, играет роль копирующего конструктора
        // При ValueType, совпадающем с const Type, играет роль конвертирующего конструктора
        BasicIterator(const BasicIterator<Type> &other) noexcept {
            //  assert(false);
            // Реализуйте конструктор самостоятельно
            node_ = other.node_;
            
        }

        // Чтобы компилятор не выдавал предупреждение об отсутствии оператора = при наличии
        // пользовательского конструктора копирования, явно объявим оператор = и
        // попросим компилятор сгенерировать его за нас
        BasicIterator &operator=(const BasicIterator &rhs) = default;

        // Оператор сравнения итераторов (в роли второго аргумента выступает константный итератор)
        // Два итератора равны, если они ссылаются на один и тот же элемент списка либо на end()
        [[nodiscard]] bool operator==(const BasicIterator<const Type> &rhs) const noexcept {
            // assert(false);
            // Заглушка. Реализуйте оператор самостоятельно
            return node_ == rhs.node_;
        }

        // Оператор проверки итераторов на неравенство
        // Противоположен !=
        [[nodiscard]] bool operator!=(const BasicIterator<const Type> &rhs) const noexcept {
            // assert(false);
            // Заглушка. Реализуйте оператор самостоятельно
            return node_ != rhs.node_;
        }

        // Оператор сравнения итераторов (в роли второго аргумента итератор)
        // Два итератора равны, если они ссылаются на один и тот же элемент списка либо на end()
        [[nodiscard]] bool operator==(const BasicIterator<Type> &rhs) const noexcept {
            // assert(false);
            // Заглушка. Реализуйте оператор самостоятельно
            return node_ == rhs.node_;
        }

        // Оператор проверки итераторов на неравенство
        // Противоположен !=
        [[nodiscard]] bool operator!=(const BasicIterator<Type> &rhs) const noexcept {
            // assert(false);
            //  Заглушка. Реализуйте оператор самостоятельно
            return node_ != rhs.node_;
        }

        // Оператор прединкремента. После его вызова итератор указывает на следующий элемент списка
        // Возвращает ссылку на самого себя
        // Инкремент итератора, не указывающего на существующий элемент списка, приводит к неопределённому поведению
        BasicIterator &operator++() noexcept {
           // if (node_->next_node) {
            node_ = node_->next_node;
           // return *this;
           // }
            return *this;
        }

        // Оператор постинкремента. После его вызова итератор указывает на следующий элемент списка
        // Возвращает прежнее значение итератора
        // Инкремент итератора, не указывающего на существующий элемент списка,
        // приводит к неопределённому поведению
        BasicIterator operator++(int) noexcept {
            // auto old_value = new BasicIterator<ValueType>; // Сохраняем прежнее значение объекта для последующего возврата
            auto old_value(*this); // Сохраняем прежнее значение объекта для последующего возврата
            ++(*this);        // используем логику префиксной формы инкремента
            return old_value;
        }

        // Операция разыменования. Возвращает ссылку на текущий элемент
        // Вызов этого оператора у итератора, не указывающего на существующий элемент списка,
        // приводит к неопределённому поведению
        [[nodiscard]] reference operator*() const noexcept {
            // assert(false);
            // Не реализовано
            // Заглушка. Реализуйте оператор самостоятельно
            return node_->value;
        }

        // Операция доступа к члену класса. Возвращает указатель на текущий элемент списка
        // Вызов этого оператора у итератора, не указывающего на существующий элемент списка,
        // приводит к неопределённому поведению
        [[nodiscard]] pointer operator->() const noexcept {
            //assert(false);
            // Заглушка. Реализуйте thisоператор самостоятельно
           // auto tmp = new Type(node_->value);
            
          //  items_.push_back(new T(*ptr));   
            return &node_->value;
        }

    private:
        Node *node_ = nullptr;
    };

public:
    using value_type = Type;
    using reference = value_type &;
    using const_reference = const value_type &;

    // Итератор, допускающий изменение элементов списка
    using Iterator = BasicIterator<Type>;
    // Константный итератор, предоставляющий доступ для чтения к элементам списка
    using ConstIterator = BasicIterator<const Type>;

    // Возвращает итератор, ссылающийся на первый элемент
    // Если список пустой, возвращённый итератор будет равен end()
    [[nodiscard]] Iterator begin() noexcept {
        // assert(false);
        //  Реализуйте самостоятельно
        if (size_) {
        return Iterator{head_.next_node};    
        }
        return end();
    }

    // Возвращает итератор, указывающий на позицию, следующую за последним элементом односвязного списка
    // Разыменовывать этот итератор нельзя — попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] Iterator end() noexcept {
        // assert(false);
        //  Реализуйте самостоятельно
        return Iterator{nullptr};
    }

    // Возвращает константный итератор, ссылающийся на первый элемент
    // Если список пустой, возвращённый итератор будет равен end()
    // Результат вызова эквивалентен вызову метода cbegin()
    [[nodiscard]] ConstIterator begin() const noexcept {
        // assert(false);
        //  Реализуйте самостоятельно
        return cbegin();
    }

    // Возвращает константный итератор, указывающий на позицию, следующую за последним элементом односвязного списка
    // Разыменовывать этот итератор нельзя — попытка разыменования приведёт к неопределённому поведению
    // Результат вызова эквивалентен вызову метода cend()
    [[nodiscard]] ConstIterator end() const noexcept {
        // assert(false);
        //  Реализуйте самостоятельно
        return cend();
    }

    // Возвращает константный итератор, ссылающийся на первый элемент
    // Если список пустой, возвращённый итератор будет равен cend()
    [[nodiscard]] ConstIterator cbegin() const noexcept {
        // assert(false);
        //  Реализуйте самостоятельно
        if (size_) {
        return Iterator{head_.next_node};    
        }
        return cend();
    }

    // Возвращает константный итератор, указывающий на позицию, следующую за последним элементом односвязного списка
    // Разыменовывать этот итератор нельзя — попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] ConstIterator cend() const noexcept {
        //    assert(false);
        return Iterator{nullptr};
    }

//public:
    SingleLinkedList() {
        Node();
        size_ = 0;
    }
    // Возвращает количество элементов в списке
    [[nodiscard]] size_t GetSize() const noexcept {
        return size_;

        assert(false);
        return 42;
    }

    // Сообщает, пустой ли список
    [[nodiscard]] bool IsEmpty() const noexcept {
        if (!head_.next_node) {
            return true;
        }
        //   assert(false);
        return false;
    }

    // Вставляет элемент value в начало списка за время O(1)
    void PushFront(const Type &value) {
        head_.next_node = new Node(value, head_.next_node);
        ++size_;
    }
    // Очищает список за время O(N)
    void Clear() noexcept {

        while (head_.next_node) {
            auto tmp = head_.next_node->next_node;
            delete head_.next_node;
            head_.next_node = tmp;
        }
        size_ = 0;
    }

    ~SingleLinkedList() {
        Clear();
    }

private:
    // Фиктивный узел, используется для вставки "перед первым элементом"
    Node head_;
    size_t size_;
};

// Эта функция тестирует работу SingleLinkedList
void Test2() {
    // Итерирование по пустому списку
    // Итерирование по непустому списку
    {
        SingleLinkedList<int> list;
       // const auto &const_list = list;

        list.PushFront(1);
        
       // *list.begin() = -1;

        const auto old_begin = list.cbegin();
        list.PushFront(2);

        const auto new_begin = list.cbegin();
        // Проверка прединкремента
        {
            auto new_begin_copy(new_begin);
            assert((++(new_begin_copy)) == old_begin);
        }
        // Проверка постинкремента
        {
            auto new_begin_copy(new_begin);
           assert(((new_begin_copy)++) == new_begin);
            assert(new_begin_copy == old_begin);
        }
        // Итератор, указывающий на позицию после последнего элемента, равен итератору end()
        {
            auto old_begin_copy(old_begin);
            assert((++old_begin_copy) == list.end());
            //list.end());
        }
    }
    // Преобразование итераторов
    {
        SingleLinkedList<int> list;
        list.PushFront(1);
        // Конструирование ConstIterator из Iterator
        SingleLinkedList<int>::ConstIterator const_it(list.begin());
        assert(const_it == list.cbegin());
        assert(*const_it == *list.cbegin());

        SingleLinkedList<int>::ConstIterator const_it1;
        // Присваивание ConstIterator'у значения Iterator
        const_it1 = list.begin();
        assert(const_it1 == const_it);
    }
    // Проверка оператора ->
    {
        using namespace std;
        SingleLinkedList<std::string> string_list;

        string_list.PushFront("one"s);
        assert(string_list.cbegin()->length() == 3u);
        string_list.begin()->push_back('!');
        assert(string_list.cbegin()->length() == 4u);
        assert(*string_list.begin() == "one!"s);
    }
}

int main() {
    Test2();
}

