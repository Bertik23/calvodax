#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <memory>

#include "numberrepresentation.h"

#include "../typedefs.h"

class Integer{
public:
    Integer() = default;
    Integer(const std::string &);
    Integer(i32);
    ~Integer() = default;
    //Integer & operator = (const Integer &);
    //Integer & operator = (Integer &&);
    Integer operator + (const Integer &) const;
    Integer operator - (const Integer &) const;
    Integer operator * (const Integer &) const;
    //Integer operator - () const;
    Integer operator / (const Integer &) const;
    Integer operator % (const Integer &) const;
    //Integer operator ^ (const Integer &) const;
    //Integer operator | (const Integer &) const;
    //Integer operator & (const Integer &) const;
    bool operator < (const Integer &) const;
    bool operator <= (const Integer &) const;
    bool operator > (const Integer &) const;
    bool operator >= (const Integer &) const;
    bool operator == (const Integer &) const;
    //bool operator == (const Integer &) const;
    Integer & operator += (const Integer &);
    Integer & operator -= (const Integer &);
    Integer & operator *= (const Integer &);
    Integer & operator /= (const Integer &);
    Integer & operator %= (const Integer &);
    //Integer & operator ^= (const Integer &);
    //Integer & operator |= (const Integer &);
    //Integer & operator &= (const Integer &);
    void print(std::ostream &) const;
    friend std::ostream & operator << (std::ostream & os, const Integer & n){
        n.print(os);
        return os;
    }
    bool is_zero() const;
    //Integer abs() const;
    Integer * clone() const;
protected:
    std::shared_ptr<NumberRepresentation> number;
};
