#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct Cat {
    Cat(const string& name, int age)
        : name_(name)
        , age_(age)  //
    {
        cout << name_ << " cat was created"s << endl;
    }
    const string& GetName() const noexcept {
        return name_;
    }
    int GetAge() const noexcept {
        return age_;
    }
    ~Cat() {
        cout << name_ << " cat was destroyed"s << endl;
    }
    void Speak() const {
        cout << "Meow!"s << endl;
    }

private:
    string name_;
    int age_;
};

int main() {
    Cat* cat = new Cat("Tom"s, 2);
    unique_ptr<Cat> p{cat};
    p->Speak();
    // Деструктор p удалит кота
}