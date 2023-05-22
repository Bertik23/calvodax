#include "rational.h"

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

Rational & Rational::operator += (const Rational & other){
    numerator = numerator * other.denominator + other.numerator * denominator;
    denominator *= other.denominator;
    simplify();
    return *this;
}

Rational & Rational::operator -= (const Rational & other){
    numerator = numerator * other.denominator - other.numerator * denominator;
    denominator *= other.denominator;
    simplify();
    return *this;
}

Rational & Rational::operator *= (const Rational & other){
    numerator = numerator * other.numerator;
    denominator *= other.denominator;
    simplify();
    return *this;
}

Rational & Rational::operator /= (const Rational & other){
    numerator = numerator * other.denominator;
    denominator *= other.numerator;
    simplify();
    return *this;
}

Rational Rational::operator + (const Rational & other) const{
    return Rational(*this) += other;
}
Rational Rational::operator - (const Rational & other) const{
    return Rational(*this) -= other;
}
Rational Rational::operator * (const Rational & other) const{
    return Rational(*this) *= other;
}
Rational Rational::operator / (const Rational & other) const{
    return Rational(*this) /= other;
}


bool Rational::operator <  (const Rational & other) const {
    return numerator * other.denominator < other.numerator * denominator;
}
bool Rational::operator <= (const Rational & other) const {
    return numerator * other.denominator <= other.numerator * denominator;
}
bool Rational::operator >  (const Rational & other) const {
    return numerator * other.denominator > other.numerator * denominator;
}
bool Rational::operator >= (const Rational & other) const {
    return numerator * other.denominator >= other.numerator * denominator;
}
bool Rational::operator == (const Rational & other) const {
    return numerator == other.numerator && denominator == other.denominator;
}

std::ostream & operator << (std::ostream & os, const Rational & r){
    if (r.denominator == 1){
        return os << r.numerator;
    } else 
        return os << "(" << r.numerator << " / " << r.denominator << ")";
}