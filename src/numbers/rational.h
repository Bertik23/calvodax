#pragma once

#ifdef INTEGER

#include "integer.h"

class Rational : public Number {
public:
    Rational(Integer num, Integer denom = Integer(1));
    virtual Rational operator + (const Rational &) const;
    virtual Rational operator - (const Rational &) const;
    virtual Rational operator * (const Rational &) const;
    virtual Rational operator - () const;
    virtual Rational operator / (const Rational &) const;
    virtual Rational operator % (const Rational &) const;
    //virtual Rational operator ^ (const Rational Number &) const;
    //virtual Rational operator | (const Rational Number &) const;
    //virtual Rational operator & (const Rational Number &) const;
    virtual bool operator < (const Rational &) const;
    virtual bool operator <= (const Rational &) const;
    virtual bool operator > (const Rational &) const;
    virtual bool operator >= (const Rational &) const;
    virtual bool operator == (const Rational &) const;
    virtual Rational & operator += (const Rational &);
    virtual Rational & operator -= (const Rational &);
    virtual Rational & operator *= (const Rational &);
    virtual Rational & operator /= (const Rational &);
    virtual Rational & operator %= (const Rational &);
    //virtual Rational Number & operator ^= (const Rational Number &);
    //virtual Rational Number & operator |= (const Rational Number &);
    //virtual Rational Number & operator &= (const Rational Number &);
private:
    void simplify();
    Integer numerator; // The upper number
    Integer denominator; // The lower number
};

#endif