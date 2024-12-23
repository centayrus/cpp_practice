#include <iostream>
#include <memory>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;
    // Выведет true
    std::cout << std::is_nothrow_move_constructible_v<std::string> << std::endl;
    // Выведет false
    std::cout << std::is_copy_constructible_v<std::unique_ptr<int>> << std::endl;
}