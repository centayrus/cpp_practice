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
    return rational1 += rational2;
}
// вычитание
Rational operator-(Rational rational1, Rational rational2) {
    return rational1 -= rational2;
}
//
Rational operator*(Rational rat1, Rational rat2) {
    return rat1 *= rat2;
}
Rational operator/(Rational rat1, Rational rat2) {
    return rat1 /= rat1;
}
bool operator==(Rational rat1, Rational rat2) {
    return rat1.Numerator() == rat2.Numerator() && rat1.Denominator() == rat2.Denominator();
}
bool operator!=(Rational rat1, Rational rat2) {
    return !(rat1.Numerator() == rat2.Numerator() && rat1.Denominator() == rat2.Denominator());
}
bool operator<=(Rational rat1, Rational rat2) {
    int n1 = rat1.Numerator() * rat2.Denominator();
    int n2 = rat2.Numerator() * rat1.Denominator();
    return n1 <= n2;
}
bool operator>=(Rational rat1, Rational rat2) {
    int n1 = rat1.Numerator() * rat2.Denominator();
    int n2 = rat2.Numerator() * rat1.Denominator();
    return n1 >= n2;
}
bool operator<(Rational rat1, Rational rat2) {
    int n1 = rat1.Numerator() * rat2.Denominator();
    int n2 = rat2.Numerator() * rat1.Denominator();
    return n1 < n2;
}
bool operator>(Rational rat1, Rational rat2) {
    int n1 = rat1.Numerator() * rat2.Denominator();
    int n2 = rat2.Numerator() * rat1.Denominator();
    return n1 > n2;
}

int main() {
    Rational r1{1, 6};
    Rational r2{1, 5};
    Rational r3 = (r1 + r2) * r1;
    cout << r3 << endl;  // Выведет 1/12
    Rational r4 = r1 + r2;
    cout << r4 << endl;  // Выведет 1/12
    bool i = r1 > r1;
    cout << i;
}