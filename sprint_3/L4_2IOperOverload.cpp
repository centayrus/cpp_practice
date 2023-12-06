#include <numeric>
#include <iostream>

using namespace std;

class Rational {
public:
    Rational() = default;

    Rational(int numerator)
        : numerator_(numerator)
        , denominator_(1) {
    }

    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {
        Normalize();
    }

    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

    
 

private:
    void Normalize() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};
//вывод
 ostream& operator<<(ostream& output, Rational rat) {
    output << rat.Numerator() << "/" << rat.Denominator();
    return output;
}

// ввод
istream& operator>>(istream& input, Rational& rat)  {
    int x, y;
     char comma; // переменная для считывания запятой
    input >> x >> comma >> y;
    rat = Rational{x, y};
    return input;
}   
