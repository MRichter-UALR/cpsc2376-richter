#ifndef MIXEDFRACTION_H
#define MIXEDFRACTION_H

#include "Fraction.h"
#include <iostream>

class MixedFraction : public Fraction {
public:
    // Constructors
    MixedFraction(int whole, int n, int d);
    MixedFraction(const Fraction& fraction);
};

// Stream output
std::ostream& operator<<(std::ostream& os, const MixedFraction& mf);

#endif
