#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Animal {
public:
    virtual ~Animal() = default;

protected:
    int health_ = 10;
};

class Mouse : public Animal {
public:
    void EatCheese() {
        health_ += 10;
    }
};

class Hedgehog : public Animal {
public:
    void Sing(string song) {
        sing_history_.push_back(move(song));
    }

private:
    vector<string> sing_history_;
};


void PlayWithAnimal(Animal& animal) {
    Mouse& mouse = dynamic_cast<Mouse&>(animal);
    cout << "Mouse eats cheese"sv << endl;
    mouse.EatCheese();

    Hedgehog& hedgehog = dynamic_cast<Hedgehog*>(animal);
    cout << "Hedgehog sings songs"sv << endl;
    hedgehog.Sing("Jingle Bells"s);
    hedgehog.Sing("Yesterday"s);
}

int main() {
    Mouse mouse;
    PlayWithAnimal(mouse);
    cout << "---"sv << endl;
    Hedgehog hedgehog;
    PlayWithAnimal(hedgehog);
}