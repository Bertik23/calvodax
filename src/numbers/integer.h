/** @file */
#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <memory>

#include "numberrepresentation.h"

#include "../typedefs.h"

class Integer{
public:
    /// @brief makes invalid integer
    /// @deprecated
    Integer() = default;
    /// @brief Constructs integer from decimal or hexadecimal string
    Integer(const std::string &);
    /// @brief Constructs integer from i32
    Integer(i32);
    /// @brief Constructs integer from digits
    Integer(Digits);
    Integer operator + (const Integer &) const;
    Integer operator - (const Integer &) const;
    Integer operator - () const;
    Integer operator * (const Integer &) const;
    /// @brief Divides two numbers.
    /// 
    /// A really slow algorithm.
    /// @throw std::logic_error when dividing by zero
    Integer operator / (const Integer &) const;
    /// @brief Returns remainder after dividing two numbers.
    /// 
    /// A really slow algorithm.
    /// @throw std::logic_error when dividing by zero
    Integer operator % (const Integer &) const;
    bool operator < (const Integer &) const;
    bool operator <= (const Integer &) const;
    bool operator > (const Integer &) const;
    bool operator >= (const Integer &) const;
    bool operator == (const Integer &) const;
    Integer & operator += (const Integer &);
    Integer & operator -= (const Integer &);
    Integer & operator *= (const Integer &);
    Integer & operator /= (const Integer &);
    Integer & operator %= (const Integer &);
    void print(std::ostream &) const;
    bool is_zero() const;
    /// @brief Makes a heap alloced deep copy and return pointer to it.
    ///
    /// Uses copy construtor to make it (shallow copy)
    Integer * clone() const;
    Integer power(const Integer &) const;
    /// @brief Divides two numbers and returns division results.
    /// @throw std::logic_error when dividing by zero
    /// @return std::pair<Digits,Digits> first is division result, second is
    /// remainder.
    static std::pair<Integer, Integer> divide(const Integer &, const Integer &);
protected:
    std::shared_ptr<NumberRepresentation> number;
};

std::ostream & operator << (std::ostream & os, const Integer & n);