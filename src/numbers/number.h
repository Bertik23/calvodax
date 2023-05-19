#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "../typedefs.h"

class Number{
public:
    Number();
    Number(i32);
    Number(const std::vector<u32> &, bool);
    Number(std::vector<u32> &&, bool);
    Number(const Number &);
    Number(Number &&);
    Number(const std::string &);
    virtual ~Number();
    virtual Number & operator = (const Number &);
    virtual Number & operator = (Number &&);
    virtual Number operator + (const Number &) const;
    virtual Number operator - (const Number &) const;
    virtual Number operator * (const Number &) const;
    virtual Number operator - () const;
    virtual Number operator / (const Number &) const;
    virtual Number operator % (const Number &) const;
    //virtual Number operator ^ (const Number &) const;
    //virtual Number operator | (const Number &) const;
    //virtual Number operator & (const Number &) const;
    virtual bool operator < (const Number &) const;
    virtual bool operator <= (const Number &) const;
    virtual bool operator > (const Number &) const;
    virtual bool operator >= (const Number &) const;
    virtual bool operator == (const Number &) const;
    //virtual bool operator == (const Number &) const;
    virtual Number & operator += (const Number &);
    virtual Number & operator -= (const Number &);
    virtual Number & operator *= (const Number &);
    virtual Number & operator /= (const Number &);
    virtual Number & operator %= (const Number &);
    //virtual Number & operator ^= (const Number &);
    //virtual Number & operator |= (const Number &);
    //virtual Number & operator &= (const Number &);
    virtual void print(std::ostream &) const;
    friend std::ostream & operator << (std::ostream & os, const Number & n){
        n.print(os);
        return os;
    }
    virtual bool is_zero() const;
    virtual Number abs() const;
    virtual Number * clone() const;
private:
    static std::pair<Number, Number> divide(Number, const Number &);
    static void print_rec(std::ostream &, const Number &);
    // static u32 find_digit(const Number &, const Number &);
    std::vector<u32> numbers;
    bool is_negative = false;
    virtual Number operator >> (u32) const;
    virtual Number & operator >>= (u32);
};
