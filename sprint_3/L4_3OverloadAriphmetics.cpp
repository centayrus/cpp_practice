#include <iostream>
#include <numeric>

using namespace std;

class Rational {
public:
    Rational() = default;

    Rational(int numerator)
        : numerator_(numerator)
        , denominator_(1)
    {
    }

    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator)
    {
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
        int n = gcd(numerator_, denominator_);
        numerator_ /= n;
        denominator_ /= n;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};

ostream& operator<<(ostream& output, Rational rational) {
    output << rational.Numerator() << '/' << rational.Denominator();
    return output;
}

istream& operator>>(istream& input, Rational& rational) {
    int numerator, denominator;
    char slash;
    input >> numerator >> slash >> denominator;
    rational = Rational{numerator, denominator};
    return input;
}

// унарный плюс
Rational operator+(Rational rational) {
    return rational;
}

// унарный минус
Rational operator-(Rational rational) {
    int numer = rational.Numerator();
    int denomin = rational.Denominator();
    return {-numer, denomin};
}
// сложение
Rational operator+(Rational rational1, Rational rational2) {
    int numerator = (rational1.Numerator()*rational2.Denominator()) + (rational2.Numerator()*rational1.Denominator());
    int denominator = rational1.Denominator()*rational2.Denominator();
    return {numerator, denominator};
}

// вычитание
Rational operator-(Rational rational1, Rational rational2) {
    int numerator = (rational1.Numerator()*rational2.Denominator()) - (rational2.Numerator()*rational1.Denominator());
    int denominator = rational1.Denominator()*rational2.Denominator();
    return {numerator, denominator};
}


