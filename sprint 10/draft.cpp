#include <iostream>

using namespace std;

class Animal {
public:
    virtual ~Animal() = default;
    virtual string GetType() const {
        return "unknown"s;
    }
};

class Mouse : public Animal {
public:
    string GetType() const override {
        return "mouse"s;
    }
};

class Frog : public Animal {
public:
    string GetType() const override {
        return "frog"s;
    }
};

int main() {
    try {
        throw Mouse();
    } catch (const Animal &animal) {
        cout << "Caught an animal of type: "sv << animal.GetType() << endl;
    }
} 