#include <cassert>
#include <string>
#include <string_view>


// Решение, использующее рекурсию
/*
template <typename T>
bool EqualsToOneOf(const T&) {
    return false;
}
template <typename T, typename U, typename... Other>
bool EqualsToOneOf(const T& x, const U& y, const Other&... other) {
    return (x == y) || EqualsToOneOf(x, other...);
}
*/

/* Напишите вашу реализацию EqualsToOneOf здесь*/
template <typename T0, typename... Ts>
bool EqualsToOneOf(const T0 &v0, const Ts &...vs) {

    if constexpr (sizeof...(vs) == 0) {
        return false;
    }
    return (... || (v0 == vs)); // Используем fold expression
}

int main() {
    using namespace std::literals;
    assert(EqualsToOneOf("hello"sv, "hi"s, "hello"s));
    assert(!EqualsToOneOf(1, 10, 2, 3, 6));
    assert(!EqualsToOneOf(8));
}