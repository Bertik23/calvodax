#include "rational.h"

#ifdef RATIONAL

#include "../utils/gcd.h"

Rational::Rational(Integer num, Integer denom)
    : numerator(num),
      denominator(denom)
{
    simplify();
}

void Rational::simplify(){
    Integer g = gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;
}

#endif