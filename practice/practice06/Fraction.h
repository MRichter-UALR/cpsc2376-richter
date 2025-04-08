#ifndef FRACTION_H
#define FRACTION_H

#include <stdexcept>
#include <iostream>

class Fraction {
private:
    int num;
    int den;
    void simplify(); // Helper function to reduce the fraction

public:
    // Constructors
    Fraction();
    Fraction(int n, int d);

    // Getters
    int getNumerator() const;
    int getDenominator() const;

    // Setters
    void setNumerator(int n);
    void setDenominator(int d);
};

// Arithmetic operator overloads
Fraction operator+(const Fraction& lhs, const Fraction& rhs);
Fraction operator-(const Fraction& lhs, const Fraction& rhs);
Fraction operator*(const Fraction& lhs, const Fraction& rhs);
Fraction operator/(const Fraction& lhs, const Fraction& rhs);

// Stream insertion (<<) overload
std::ostream& operator<<(std::ostream& os, const Fraction& frac);

#endif
