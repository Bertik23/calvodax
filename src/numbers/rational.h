#pragma once

#include "integer.h"

class Rational {
public:
    Rational(Integer num, Integer denom = Integer(1));
    Rational operator + (const Rational &) const;
    Rational operator - (const Rational &) const;
    Rational operator * (const Rational &) const;
    //Rational operator - () const;
    Rational operator / (const Rational &) const;
    //Rational operator % (const Rational &) const;
    //Rational operator ^ (const Rational Number &) const;
    //Rational operator | (const Rational Number &) const;
    //Rational operator & (const Rational Number &) const;
    bool operator < (const Rational &) const;
    bool operator <= (const Rational &) const;
    bool operator > (const Rational &) const;
    bool operator >= (const Rational &) const;
    bool operator == (const Rational &) const;
    Rational & operator += (const Rational &);
    Rational & operator -= (const Rational &);
    Rational & operator *= (const Rational &);
    Rational & operator /= (const Rational &);
    //Rational & operator %= (const Rational &);
    //Rational Number & operator ^= (const Rational Number &);
    //Rational Number & operator |= (const Rational Number &);
    //Rational Number & operator &= (const Rational Number &);
    friend std::ostream & operator << (std::ostream &, const Rational &);
private:
    void simplify();
    Integer numerator; // The upper number
    Integer denominator; // The lower number
};