#include <vector>
#include <iostream>
#include "../typedefs.h"

class Number{
public:
    Number();
    Number(i32);
    Number(const Number &);
    Number(Number &&);
    virtual Number & operator = (const Number &);
    virtual Number & operator = (Number &&);
    virtual Number operator + (const Number &) const;
    //virtual Number operator - (const Number &) const;
    virtual Number operator * (const Number &) const;
    //virtual Number operator / (const Number &) const;
    //virtual Number operator ^ (const Number &) const;
    //virtual Number operator | (const Number &) const;
    //virtual Number operator & (const Number &) const;
    virtual bool operator < (const Number &) const;
    //virtual bool operator > (const Number &) const;
    //virtual bool operator == (const Number &) const;
    virtual Number & operator += (const Number &);
    //virtual Number & operator -= (const Number &);
    virtual Number & operator *= (const Number &);
    //virtual Number & operator /= (const Number &);
    //virtual Number & operator ^= (const Number &);
    //virtual Number & operator |= (const Number &);
    //virtual Number & operator &= (const Number &);
    virtual void print(std::ostream &) const;
    friend std::ostream & operator << (std::ostream & os, const Number & n){
        n.print(os);
        return os;
    }
private:
    std::vector<u32> numbers;
    bool is_negative = false;
};