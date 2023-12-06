#include <iostream>
#include <numeric>

using namespace std;

class Rational {
   public:
    Rational() = default;

    Rational(int numerator)
        : numerator_(numerator), denominator_(1) {
    }

    Rational(int numerator, int denominator)
        : numerator_(numerator), denominator_(denominator) {
        Normalize();
    }

    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

    Rational operator+=(Rational rat2) {
        numerator_ = (numerator_ * rat2.Denominator()) + (rat2.Numerator() * denominator_);
        denominator_ *= rat2.Denominator();
        Normalize();
        return *this;
    }
    Rational operator-=(Rational rat2) {
        numerator_ = (numerator_ * rat2.Denominator()) - (rat2.Numerator() * denominator_);
        ;
        denominator_ *= rat2.Denominator();
        Normalize();
        return *this;
    }
    Rational operator*=(Rational rat2) {
        numerator_ *= rat2.Numerator();
        denominator_ *= rat2.Denominator();
        Normalize();
        return *this;
    }
    Rational operator/=(Rational rat2) {
        numerator_ *= rat2.Denominator();
        denominator_ *= rat2.Numerator();
        Normalize();
        return *this;
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
    int numerator1 = rational1.Numerator();
    numerator1 *= rational2.Denominator();
    int numerator2 = rational2.Numerator();
    numerator2 *= rational1.Denominator();
    // int numerator = (rational1.Numerator() * rational2.Denominator()) + (rational2.Numerator() * rational1.Denominator());
    int denominator = rational1.Denominator();
    denominator *= rational2.Denominator();
    return {numerator1 += numerator2, denominator};
}
// вычитание
Rational operator-(Rational rational1, Rational rational2) {
    int numerator = (rational1.Numerator() * rational2.Denominator()) - (rational2.Numerator() * rational1.Denominator());
    int denominator = rational1.Denominator() * rational2.Denominator();
    return {numerator, denominator};
}
//
Rational operator*(Rational rat1, Rational rat2) {
    int numerator1 = rat1.Numerator();
    int denominator1 = rat1.Denominator();
    return {numerator1 *= rat2.Numerator(), denominator1 *= rat2.Denominator()};
}
Rational operator/(Rational rat1, Rational rat2) {
    int numerator1 = rat1.Numerator();
    int denominator1 = rat1.Denominator();
    return {numerator1 *= rat2.Denominator(), denominator1 *= rat2.Numerator()};
}

int main() {
    Rational r1{1, 6};
    Rational r2{1, 5};
    Rational r3 = (r1 + r2) * r1;
    cout << r3 << endl;  // Выведет 1/12
    Rational r4 = r1 + r2;
    cout << r4 << endl;  // Выведет 1/12
}