#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
#include <vector>

using namespace std;


// clang-format off

//const int NUM_PLANETS = 8;
const array PLANETS = {
    "Mercury"sv, "Venus"sv, "Earth"sv,
    "Mars"sv, "Jupiter"sv, "Saturn"sv,
    "Uranus"sv, "Neptune"sv,
};

// clang-format on
bool IsPlanet(string_view name) {
    auto pos = std::find(PLANETS.begin(), PLANETS.end(), name);
    return pos != PLANETS.end();
}

void Test(string_view name) {
    cout << name << " is " << (IsPlanet(name) ? ""sv : "NOT "sv)
        << "a planet"sv << endl;
}

string ReadLine()
{
    string s;
    std::getline(cin, s);
    return s;
}

int main() {
    Test(ReadLine());
    Test(ReadLine());
    Test(ReadLine());
    Test(ReadLine());
}