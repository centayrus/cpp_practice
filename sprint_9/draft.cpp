#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string text = "100m to Marushkino";
    std::string delimiter = "to ";
    auto start_pos = text.find(delimiter);

    if (start_pos != std::string::npos) {
        start_pos += delimiter.length(); // Сдвигаем позицию на длину разделителя
        std::string result = text.substr(start_pos);
        std::cout << "Текст после 'to ': " << result << std::endl;
    } else {
        std::cout << "Разделитель 'to ' не найден." << std::endl;
    }

    return 0;
}
