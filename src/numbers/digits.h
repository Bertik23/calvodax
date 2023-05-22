#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "../typedefs.h"

class Digits {
public:
    Digits();
    Digits(i32);
    Digits(u32);
    Digits(const std::vector<u32> &, bool);
    Digits(std::vector<u32> &&, bool);
    Digits(const Digits &);
    Digits(Digits &&);
    Digits(const std::string &);
    virtual ~Digits();
    virtual Digits & operator = (const Digits &);
    virtual Digits & operator = (Digits &&);
    virtual Digits operator + (const Digits &) const;
    virtual Digits operator - (const Digits &) const;
    virtual Digits operator * (const Digits &) const;
    virtual Digits operator - () const;
    virtual Digits operator / (const Digits &) const;
    virtual Digits operator % (const Digits &) const;
    //virtual Digits operator ^ (const Digits &) const;
    //virtual Digits operator | (const Digits &) const;
    //virtual Digits operator & (const Digits &) const;
    virtual bool operator < (const Digits &) const;
    virtual bool operator <= (const Digits &) const;
    virtual bool operator > (const Digits &) const;
    virtual bool operator >= (const Digits &) const;
    virtual bool operator == (const Digits &) const;
    //virtual bool operator == (const Digits &) const;
    virtual Digits & operator += (const Digits &);
    virtual Digits & operator -= (const Digits &);
    virtual Digits & operator *= (const Digits &);
    virtual Digits & operator /= (const Digits &);
    virtual Digits & operator %= (const Digits &);
    //virtual Digits & operator ^= (const Digits &);
    //virtual Digits & operator |= (const Digits &);
    //virtual Digits & operator &= (const Digits &);
    virtual void print(std::ostream &) const;
    friend std::ostream & operator << (std::ostream & os, const Digits & n){
        n.print(os);
        return os;
    }
    virtual bool is_zero() const;
    virtual Digits abs() const;
    virtual Digits * clone() const;
private:
    static std::pair<Digits, Digits> divide(Digits, const Digits &);
    static void print_rec(std::ostream &, const Digits &);
    // static u32 find_digit(const Digits &, const Digits &);
    std::vector<u32> numbers;
    bool is_negative = false;
    virtual Digits operator >> (u32) const;
    virtual Digits & operator >>= (u32);
};
