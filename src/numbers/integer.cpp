#include "number.h"
#include <cmath>


Number::Number() = default;

Number::Number(i32 i)
    : numbers{(u32) std::abs(i)},
      is_negative(i < 0){}

Number::Number(const Number & o) = default;
Number::Number(Number && o) = default;
Number & Number::operator = (const Number &) = default;
Number & Number::operator = (Number &&) = default;

Number & Number::operator += (const Number & other){
    std::size_t i = 0;
    u32 cary = 0;
    for (;
         i < std::min(numbers.size(), other.numbers.size());
        ++i
    ){
        auto prev = numbers[i];
        numbers[i] += other.numbers[i] + cary;
        if (numbers[i] < prev){
            cary = 1;
        } else cary = 0;
    }
    while (cary){
        if (i < numbers.size()){
            // i >= other.numbers.size()
            auto prev = numbers[i];
            numbers[i] += cary;
            if (numbers[i] < prev){
                cary = 1;
            } else cary = 0;
        } else if (i >= numbers.size() && i < other.numbers.size()) {
            numbers.push_back(other.numbers[i] + cary);
            if (numbers[i] < other.numbers[i]){
                cary = 1;
            } else cary = 0;
        } else if (i >= numbers.size() && i >= other.numbers.size()){
            numbers.push_back(cary);
            cary = 0;
        }
        ++i;
    }
    while(i < other.numbers.size()){
        numbers.push_back(other.numbers[i++]);
    }
    return *this;
}

Number Number::operator + (const Number & other) const{
    Number tmp(*this);
    return tmp += other;
}

/**
 * Print big int
*/
void Number::print(std::ostream & os) const {
    if (is_negative){
        os << "-";
    }
    
    for (auto & i: numbers){
        os << i;
        os << ", ";
    }
}

Number & Number::operator *= (const Number & other){
    std::size_t i = 0;
    u32 cary = 0;
    for (;
         i < std::min(numbers.size(), other.numbers.size());
        ++i
    ){
        // auto prev = numbers[i];
        u64 o = (u64)numbers[i] * (u64)other.numbers[i] + cary;

        std::cout << o << std::endl;
        std::cout << (o & (((u64)1<<33) - 1)) << std::endl;
        std::cout << (o >> 32) << std::endl;

        numbers[i] = o & (((u64)1<<33) - 1);
        cary = o >> 32;
        // if (numbers[i] < prev){
        //     cary = 1;
        // } else cary = 0;
    }
    while (cary){
        if (i < numbers.size()){
            // i >= other.numbers.size()
            auto prev = numbers[i];
            numbers[i] += cary;
            if (numbers[i] < prev){
                cary = 1;
            } else cary = 0;
        } else if (i >= numbers.size() && i < other.numbers.size()) {
            numbers.push_back(other.numbers[i] + cary);
            if (numbers[i] < other.numbers[i]){
                cary = 1;
            } else cary = 0;
        } else if (i >= numbers.size() && i >= other.numbers.size()){
            numbers.push_back(cary);
            cary = 0;
        }
        ++i;
    }
    while(i < other.numbers.size()){
        numbers.push_back(other.numbers[i++]);
    }
    return *this;
}

Number Number::operator * (const Number & other) const{
    Number tmp(*this);
    return tmp *= other;
}