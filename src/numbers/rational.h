/** @file */
#pragma once

#include "integer.h"

class Rational {
public:
    /**
     * @brief Constructs rational number with a numerator and denominator.
     * 
     * @param num numerartor
     * @param denom denominator, defaults to 1
     * @throw std::logic_error if denominator is 0
    */
    Rational(Integer num, Integer denom = Integer(1));
    /// @brief Adds two rationals
    Rational operator + (const Rational &) const;
    /// @brief Subtracts two rationals
    Rational operator - (const Rational &) const;
    /// @brief Multiplies two rationals
    Rational operator * (const Rational &) const;
    /// @brief Divides two rationals
    /// @throw std::logic_error when dividing by zero
    Rational operator / (const Rational &) const;
    /// @brief Returns modulo two rationals if both are integers.
    /// @throw std::logic_error when dividing by zero
    /// @throw text_error when at least one of the two numbers it not an integer
    Rational operator % (const Rational &) const;
    /// @brief Compares two numbers
    bool operator < (const Rational &) const;
    /// @brief Compares two numbers
    bool operator <= (const Rational &) const;
    /// @brief Compares two numbers
    bool operator > (const Rational &) const;
    /// @brief Compares two numbers
    bool operator >= (const Rational &) const;
    /// @brief Compares two numbers
    bool operator == (const Rational &) const;
    Rational & operator += (const Rational &);
    Rational & operator -= (const Rational &);
    Rational & operator *= (const Rational &);
    Rational & operator /= (const Rational &);
    Rational & operator %= (const Rational &);
    friend std::ostream & operator << (std::ostream &, const Rational &);
    Rational * clone() const;
    Rational power(const Rational &) const;
    Rational floor() const;
    Rational ceil() const;
    Rational round() const;
    const Integer & num() const;
    const Integer & denom() const;
private:
    /// @brief Simplifies rational
    void simplify();
    Integer numerator; // The upper number
    Integer denominator; // The lower number
};