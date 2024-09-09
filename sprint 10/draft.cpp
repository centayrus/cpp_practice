#include <iostream>

enum class Color { Red, Green, Blue };
enum class Shape { Circle, Square, Triangle };

std::ostream& operator<<(std::ostream& os, const Color& color) {
    switch (color) {
        case Color::Red:
            os << "Красный";
            break;
        case Color::Green:
            os << "Зеленый";
            break;
        case Color::Blue:
            os << "Синий";
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Shape& shape) {
    switch (shape) {
        case Shape::Circle:
            os << "Круг";
            break;
        case Shape::Square:
            os << "Квадрат";
            break;
        case Shape::Triangle:
            os << "Треугольник";
            break;
    }
    return os;
}

int main() {
    Color myColor = Color::Green;
    Shape myShape = Shape::Circle;
    std::cout << "Мой цвет: " << myColor << ", моя форма: " << myShape << std::endl;
    return 0;
}