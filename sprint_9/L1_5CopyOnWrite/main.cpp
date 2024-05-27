#include <cassert>
#include <iostream>
#include <memory>
#include <string>

template <typename Value>
class CoW {
public:
    // Конструируем значение по умолчанию.
    CoW()
        : value_(std::make_shared<Value>()) {
    }

    // Создаём значение за счёт перемещения его из value.
    CoW(Value &&value)
        : value_(std::make_shared<Value>(std::move(value))) {
    }

    // Создаём значение из value.
    CoW(const Value &value)
        : value_(std::make_shared<Value>(value)) {
    }

    // Оператор разыменования служит для чтения значения.
    const Value &operator*() const noexcept {
        assert(value_);
        return *value_;
    }

    // Оператор -> служит для чтения полей и вызова константных методов.
    const Value *operator->() const noexcept {
        assert(value_);
        return value_.get();
    }

    // Write принимает функцию, в которую CoW передаст неконстантную ссылку на хранящееся значение.
    template <typename ModifierFn>
    void Write(ModifierFn &&modify) {
        EnsureUnique();
        // Теперь value_ — единственный владелец данных.

        std::forward<ModifierFn>(modify)(*value_);
    }

    // опасный вариант, т.к. ссылка на строку светим наружу
        Value& Write() {
        EnsureUnique();

        return *value_;
    }

private:
    std::shared_ptr<Value> value_;

    // Удостоверяемся, что текущий объект единолично владеет данными.
    // Если это не так, создаём копию и будем ссылаться на неё.
    void EnsureUnique() {
        assert(value_);

        if (value_.use_count() > 1) {
            // Кроме нас на value_ ссылается кто-то ещё, копируем содержимое value_.
            value_ = std::make_shared<Value>(*value_);
        }
    }
};

int main() {
    using namespace std::literals;

    CoW<std::string> s1("Hello");
    CoW<std::string> s2{s1};

    // Для доступа к значению используем операцию разыменования.
    std::cout << *s1 << ", "sv << *s2 << std::endl;

    // Для вызова константных методов служит стрелочка.
    std::cout << s1->size() << std::endl;

    // Оба указателя ссылаются на одну и ту же строку в памяти.
    assert(&*s1 == &*s2);
    std::cout << &*s1 << ", "sv << &*s2 << std::endl;

    using namespace std::literals;

    CoW<std::string> s3("Hello"s);
    CoW<std::string> s4{s3};

    std::cout << *s3 << " "sv << *s4 << std::endl;

    s4.Write([](auto &value) {
        // Внутри этой функции можно изменить значение, содержащееся в s2.
        value = "World"s;
        value += '!';
    });

    // Теперь s2 содержит строку "World!".
/*     std::cout << *s3 << " "sv << *s4 << std::endl;

    CoW<std::string> s5("Hello"s);

    auto &data = s5.Write();
    CoW<std::string> s6(s5);

    data = "Hi"s;
    std::cout << *s5 << " "sv << *s6; */
}