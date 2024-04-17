#include <iostream>
#include <string>

using namespace std;

struct Circle {
    double x;
    double y;
    double r;
};

struct Dumbbell {
    Circle circle1;
    Circle circle2;
    string text;
};

struct DumbbellHash {
    size_t operator()(const Dumbbell &bell) const {

        return bell.circle1.x + bell.circle1.y * (31) + bell.circle1.r * (31 * 31) +
        bell.circle2.x * (31 * 31 * 31) + bell.circle2.y * (31 * 31 * 31 * 31) + bell.circle2.r * (31 * 31 * 31 * 31 * 31)
        ;
    }

    // Альтернатива
    /*     size_t operator() (const Circle& circ) const {
        return d_hasher(circ.x) + 37 * d_hasher(circ.y) + 37*37 * d_hasher(circ.r);
    }
    size_t operator() (const Dumbbell& bell) const {
        return 37*(37*37*37 * operator()(bell.circle1) + operator()(bell.circle2))
            + s_hasher(bell.text);
    }
    hash<double> d_hasher;
    hash<string> s_hasher;
     */
};

int main() {
    DumbbellHash hash;
    Dumbbell dumbbell{{10, 11.5, 2.3}, {3.14, 15, -8}, "abc"s};
    cout << "Dumbbell hash "s << hash(dumbbell) << endl;;
}