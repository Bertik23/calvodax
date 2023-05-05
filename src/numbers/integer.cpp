#include "number.h"
#include <cmath>
#include <iomanip>


Number::Number(): numbers(), is_negative(false){};

Number::Number(i32 i)
    : numbers{(u32) std::abs(i)},
      is_negative(i < 0){}

Number::~Number() = default;

Number::Number(const Number & o) = default;
Number::Number(Number && o) = default;
Number & Number::operator = (const Number &) = default;
Number & Number::operator = (Number &&) = default;

Number::Number(const std::vector<u32> & v, bool is_negative = false): numbers(v), is_negative(is_negative) {}
Number::Number(std::vector<u32> && v, bool is_negative = false): numbers(std::move(v)), is_negative(is_negative) {}

Number & Number::operator += (const Number & other){
    usize i = 0;
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
    usize i = 0;
    u32 cary = 0;
    is_negative = is_negative ^ other.is_negative;
    if (is_zero() || other.is_zero()){
        is_negative = false;
        numbers = {0};
        return *this;
    }
    std::vector<u32> caries{0};
    for (;
         i < std::min(numbers.size(), other.numbers.size());
        ++i
    ){
        // auto prev = numbers[i];
        u64 o = (u64)numbers[i] * (u64)other.numbers[i];

        // std::cout << std::setw(16) << std::hex << o << std::endl;
        // std::cout << std::setw(16) << (o & (((u64)1<<31) - 1)) << std::endl;
        // std::cout << std::setw(16) << (o >> 32) << std::endl;

        // std::cout << std::dec;

        numbers[i] = o & (((u64)1<<33) - 1);
        cary = o >> 32;
        caries.push_back(cary);
        // if (numbers[i] < prev){
        //     cary = 1;
        // } else cary = 0;
    }
    // std::cout << "Number: " << Number(caries) << std::endl;
    *this += Number(std::move(caries));
    return *this;
}

Number Number::operator * (const Number & other) const{
    Number tmp(*this);
    return tmp *= other;
}

bool Number::operator < (const Number & other) const {
    bool xr = false;
    if (is_negative && other.is_negative)
        xr = 1;
    else if (is_negative && !other.is_negative)
        return true;
    else if (!is_negative && other.is_negative)
        return false;
    for (usize i = std::max(other.numbers.size(), numbers.size())-1; i > 0; --i){
        if (i >= other.numbers.size() && numbers[i]){
            return false ^ xr;
        } else if (i >= numbers.size() && other.numbers[i])
            return true ^ xr;
    }
    return numbers[0] < other.numbers[0];

}

bool Number::is_zero() const {
    for (const auto & i: numbers){
        if (i)
            return false;
    }
    return true;
}