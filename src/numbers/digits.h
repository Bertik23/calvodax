/** @file */
#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "../typedefs.h"

/**
 * Represents the digit of a number.
*/
class Digits {
public:
    /// @brief Default constructor. Defaults to zero.
    Digits();
    /// @brief Constructs digits from i32
    Digits(i32);
    /// @brief Constructs digits from i32
    Digits(u32);
    /// @brief Constructs digits from u64
    Digits(u64);
    /// @brief Constructs digits from a vector of u32 digits and a sign
    Digits(const std::vector<u32> &, bool);
    /// @brief Constructs digits from a vector of u32 digits and a sign
    Digits(std::vector<u32> &&, bool);
    /// @brief Deep copies
    Digits(const Digits &);
    /// @brief Destructevely deep copies
    Digits(Digits &&);
    /// @brief Factory to make digits from string
    static Digits from_str(const std::string &);
    /// @brief Factory to make digits from decimal string
    static Digits from_dec_str(const std::string &);
    /// @brief Factory to make digits from hexadecimal string
    static Digits from_hex_str(const std::string &);
    ~Digits();
    /// @brief Asignment operator with deep copy
    Digits & operator = (const Digits &);
    /// @brief Move asignment operator with deep copy
    Digits & operator = (Digits &&);
    /// @brief Adds two numbers
    ///
    /// Adds two numbers like we learned in elementary school
    Digits operator + (const Digits &) const;
    /// @brief Subracts two numbers
    ///
    /// Subtracts two numbers like we learned in elementary school
    Digits operator - (const Digits &) const;
    /// @brief Multiplies two numbers
    ///
    /// Multiplies two numbers like we learned in elementary school
    Digits operator * (const Digits &) const;
    /// @brief Negets a number
    Digits operator - () const;
    /// @brief Divides two numbers
    ///
    /// Divides two numbers like we learned in elementary school. Every digit is
    /// guessed with binary search. A really slow algorithm.
    /// @throw std::logic_error when dividing by zero
    Digits operator / (const Digits &) const;
    /// @brief Remainder after dividing two numbers
    ///
    /// Divides two numbers like we learned in elementary school. Every digit is
    /// guessed with binary search. A really slow algorithm. Returns remainder
    /// after division.
    /// @throw std::logic_error when dividing by zero
    Digits operator % (const Digits &) const;
    /// @brief Compares two numbers.
    bool operator < (const Digits &) const;
    /// @brief Compares two numbers.
    bool operator <= (const Digits &) const;
    /// @brief Compares two numbers.
    bool operator > (const Digits &) const;
    /// @brief Compares two numbers.
    bool operator >= (const Digits &) const;
    /// @brief Compares two numbers.
    bool operator == (const Digits &) const;
    /// @brief Inplace addition
    Digits & operator += (const Digits &);
    /// @brief Inplace subtraction
    Digits & operator -= (const Digits &);
    /// @brief Inplace multiplication
    Digits & operator *= (const Digits &);
    /// @brief Inplace division
    /// @throw std::logic_error when dividing by zero
    Digits & operator /= (const Digits &);
    /// @brief Inplace modulation
    /// @throw std::logic_error when dividing by zero
    Digits & operator %= (const Digits &);
    /// @brief Prints self to output stream.
    void print(std::ostream &) const;
    /// @brief Checks if number is zero.
    bool is_zero() const;
    /// @brief Returns absolute value of number.
    Digits abs() const;
    /// @brief Makes a heap alloced deep copy and return pointer to it.
    Digits * clone() const;
    /// @brief Divides two numbers and returns division results.
    /// @throw std::logic_error when dividing by zero
    /// @return std::pair<Digits,Digits> first is division result, second is
    /// remainder.
    static std::pair<Digits, Digits> divide(Digits, const Digits &);
    /// @brief Returns binary representation of number.
    std::vector<bool> as_bits() const;
    /// @brief Exponentiates number. Using sqare and multiply.
    Digits power(const Digits &) const;
    /// @brief Returns number of digits.
    usize size() const;
    /// @brief Returns if number is < 0
    bool negative() const;
private:
    /// @brief Helper funtion for printing in decimal
    static void print_rec(std::ostream &, const Digits &);
    std::vector<u32> numbers;
    bool is_negative = false;
    /// @brief Bitshift for small number of places
    Digits operator >> (u32) const;
    /// @brief Inplace bitshift for small number of places
    Digits & operator >>= (u32);
};

/**
 * @brief Overloaded operator << for printing to output stream.
 * 
 * Uses print method to write to output stream.
*/
std::ostream & operator << (std::ostream & os, const Digits & n);