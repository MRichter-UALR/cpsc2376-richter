#include "Fraction.h"

// Default constructor
Fraction::Fraction() : num(0), den(1) {}

// Parameterized constructor
Fraction::Fraction(int n, int d) {
    if (d == 0) throw std::invalid_argument("Denominator cannot be zero.");
    num = n;
    den = d;
    simplify();
}

// Getters
int Fraction::getNumerator() const {
    return num;
}

int Fraction::getDenominator() const {
    return den;
}

// Setters
void Fraction::setNumerator(int n) {
    num = n;
    simplify();
}

void Fraction::setDenominator(int d) {
    if (d == 0) throw std::invalid_argument("Denominator cannot be zero.");
    den = d;
    simplify();
}

// Simplify using Euclidean algorithm
void Fraction::simplify() {
    if (den == 0) throw std::invalid_argument("Denominator cannot be zero.");

    int a = abs(num);
    int b = abs(den);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    int gcd = a;

    num /= gcd;
    den /= gcd;

    if (den < 0) {
        den *= -1;
        num *= -1;
    }
}

// Operator overloads
Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    int n = lhs.getNumerator() * rhs.getDenominator() + rhs.getNumerator() * lhs.getDenominator();
    int d = lhs.getDenominator() * rhs.getDenominator();
    return Fraction(n, d);
}

Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
    int n = lhs.getNumerator() * rhs.getDenominator() - rhs.getNumerator() * lhs.getDenominator();
    int d = lhs.getDenominator() * rhs.getDenominator();
    return Fraction(n, d);
}

Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
    int n = lhs.getNumerator() * rhs.getNumerator();
    int d = lhs.getDenominator() * rhs.getDenominator();
    return Fraction(n, d);
}

Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
    if (rhs.getNumerator() == 0) throw std::invalid_argument("Cannot divide by zero.");
    int n = lhs.getNumerator() * rhs.getDenominator();
    int d = lhs.getDenominator() * rhs.getNumerator();
    return Fraction(n, d);
}

std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
    os << frac.getNumerator() << "/" << frac.getDenominator();
    return os;
}
