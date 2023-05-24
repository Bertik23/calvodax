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
    Digits(u64);
    Digits(const std::vector<u32> &, bool);
    Digits(std::vector<u32> &&, bool);
    Digits(const Digits &);
    Digits(Digits &&);
    static Digits from_str(const std::string &);
    static Digits from_dec_str(const std::string &);
    static Digits from_hex_str(const std::string &);
    ~Digits();
    Digits & operator = (const Digits &);
    Digits & operator = (Digits &&);
    Digits operator + (const Digits &) const;
    Digits operator - (const Digits &) const;
    Digits operator * (const Digits &) const;
    Digits operator - () const;
    Digits operator / (const Digits &) const;
    Digits operator % (const Digits &) const;
    //Digits operator ^ (const Digits &) const;
    //Digits operator | (const Digits &) const;
    //Digits operator & (const Digits &) const;
    bool operator < (const Digits &) const;
    bool operator <= (const Digits &) const;
    bool operator > (const Digits &) const;
    bool operator >= (const Digits &) const;
    bool operator == (const Digits &) const;
    //bool operator == (const Digits &) const;
    Digits & operator += (const Digits &);
    Digits & operator -= (const Digits &);
    Digits & operator *= (const Digits &);
    Digits & operator /= (const Digits &);
    Digits & operator %= (const Digits &);
    //Digits & operator ^= (const Digits &);
    //Digits & operator |= (const Digits &);
    //Digits & operator &= (const Digits &);
    void print(std::ostream &) const;
    friend std::ostream & operator << (std::ostream & os, const Digits & n){
        n.print(os);
        return os;
    }
    bool is_zero() const;
    Digits abs() const;
    Digits * clone() const;
    static std::pair<Digits, Digits> divide(Digits, const Digits &);
    std::vector<bool> as_bits() const;
    Digits power(const Digits &) const;
    usize size() const;
    bool negative() const;
private:
    static void print_rec(std::ostream &, const Digits &);
    // static u32 find_digit(const Digits &, const Digits &);
    std::vector<u32> numbers;
    bool is_negative = false;
    Digits operator >> (u32) const;
    Digits & operator >>= (u32);
};
