#include "MixedFraction.h"
#include <cmath>

// Constructor: whole number + fraction
MixedFraction::MixedFraction(int whole, int n, int d) : Fraction(whole* d + (whole >= 0 ? n : -n), d) {
    // Initializes as improper fraction internally
}

// Constructor: from Fraction
MixedFraction::MixedFraction(const Fraction& fraction) : Fraction(fraction) {
    // Copy base class constructor
}

// Stream output
std::ostream& operator<<(std::ostream& os, const MixedFraction& mf) {
    int num = mf.getNumerator();
    int den = mf.getDenominator();

    if (std::abs(num) < den) {
        // Proper fraction
        os << num << "/" << den;
    }
    else {
        int whole = num / den;
        int remainder = std::abs(num % den);

        if (remainder == 0) {
            os << whole;
        }
        else {
            os << whole << " " << remainder << "/" << den;
        }
    }

    return os;
}
