#include "rational.h"
#include "../utils/exceptions.h"

#include "../utils/gcd.h"

Rational::Rational(Integer num, Integer denom)
    : numerator(num),
      denominator(denom)
{
    //std::cerr << num << " lomeno " << denom << std::endl;
    simplify();
}

void Rational::simplify(){
    if (denominator < 0){
        if (numerator < 0){
            numerator = -numerator;
        }
        denominator = -denominator;
    }
    if (denominator.is_zero())
        throw std::logic_error("division by zero");
    Integer g = gcd(numerator, denominator);
    if (g == 1) return;
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

Rational & Rational::operator %= (const Rational & other){
    if (!(denominator == 1) || !(other.denominator == 1))
        throw text_error("Only integers are allowed in modulo.");
    numerator %= other.numerator;
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

Rational Rational::operator % (const Rational & other) const{
    return Rational(*this) %= other;
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
        return os << "( " << r.numerator << " / " << r.denominator << " )";
}


Rational * Rational::clone() const{
    return new Rational(*this);
}

Rational Rational::power(const Rational & other) const {
    if (!(other.denominator == Integer(1)))
        throw text_error("Exponent must be an integer.");
    Rational out(0);
    out.numerator = numerator.power(other.numerator);
    out.denominator = denominator.power(other.numerator);
    return out;
}

const Integer & Rational::num() const {
    return numerator;
}

const Integer & Rational::denom() const {
    return denominator;
}

Rational Rational::floor() const {
    return Rational(numerator / denominator);
}

Rational Rational::ceil() const {
    return Rational((numerator + denominator) / denominator);
}

Rational Rational::round() const {
    auto div = Integer::divide(numerator, denominator);
    return (Rational(div.second) >= Rational(denominator, 2)) ? ceil() : div.first; 
}