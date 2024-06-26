#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::string text = "100m to Marushkino";
    std::string to_search = "to ";
    auto to_pos = std::find_end(text.begin(), text.end(), to_search.begin(), to_search.end());

    if (to_pos != text.end()) {
        auto end_pos = std::find(to_pos, text.end(), 'm');
        std::string result(to_pos + to_search.length(), end_pos != text.end() ? end_pos : text.end());
        std::cout << "Извлеченный текст: " << result << std::endl;
    }

    return 0;
}
