#include "number.h"

#include <cmath>
#include <iomanip>

#define DEC

void remove_leading_zeros(std::vector<u32> & arr){
    while (arr.size() > 1 && !arr.back()){
        arr.pop_back();
    }
}

Number::Number(): numbers(), is_negative(false){};

Number::Number(i32 i)
    : numbers{(u32) std::abs(i)},
      is_negative(i < 0){}

Number::Number(u32 i)
    : numbers{i},
      is_negative(false){}

Number::~Number() = default;

Number::Number(const Number & o) = default;
Number::Number(Number && o) = default;
Number & Number::operator = (const Number &) = default;
Number & Number::operator = (Number &&) = default;

Number::Number(const std::vector<u32> & v, bool is_negative = false)
  : numbers(v), is_negative(is_negative) {
    remove_leading_zeros(numbers);
  }
Number::Number(std::vector<u32> && v, bool is_negative = false)
  : numbers(std::move(v)), is_negative(is_negative) {
    remove_leading_zeros(numbers);
  }

Number & Number::operator += (const Number & other){
    if (other.is_negative ^ is_negative) return operator -=(-other);
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

    remove_leading_zeros(numbers);

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
    if (is_zero()) {
        os << "0";
        return;
    }
    if (is_negative){
        os << "-";
    }
    #ifdef HEX
    os << std::hex;
    usize i = 0;
    for (auto it = numbers.rbegin(); it != numbers.rend(); ++it){
        if (i) os << std::setw(8) << std::setfill('0');
        //if (i || *it != 0) ++i;
        //else continue;
        os << /* std::setw(8) << */ *it;
    }
    return;
    #endif // HEX

    #ifdef DEC
    // Decimal
    print_rec(os, *this);
    #endif // DEC
}

void Number::print_rec(std::ostream & os, const Number & x){
    if ( x < 10 )
    {
        os << x.numbers[0];
        return;
    }

    // std::cerr << "1" << std::endl;

    auto o = divide(x, 10);
    os << o.first;
    os << o.second;
    // print_rec(os, o.first);
}

Number & Number::operator *= (const Number & other){
    u32 cary = 0;
    is_negative = is_negative ^ other.is_negative;
    if (is_zero() || other.is_zero()){
        is_negative = false;
        numbers = {0};
        return *this;
    }
    Number out{0};
    for (usize i = 0;
         i < numbers.size();
         ++i
    ){
        std::vector<u32> caries{0};
        std::vector<u32> o_vec{};
        for (usize j = 0; j < i; ++j){
            o_vec.push_back(0);
            caries.push_back(0);
        }
        for (usize j = 0;
            j < other.numbers.size();
            ++j
        ){
            // auto prev = numbers[i];
            u64 o = (u64)other.numbers[j] * (u64)numbers[i];

            // std::cout << std::setw(16) << std::hex << o << std::endl;
            // std::cout << std::setw(16) << (o & (((u64)1<<31) - 1)) << std::endl;
            // std::cout << std::setw(16) << (o >> 32) << std::endl;

            // std::cout << std::dec;

            o_vec.push_back(o & (((u64)1<<33) - 1));
            cary = o >> 32;
            caries.push_back(cary);
            // if (numbers[i] < prev){
            //     cary = 1;
            // } else cary = 0;
        }
        out += caries;
        out += o_vec;
    }
    // std::cout << "Number: " << Number(caries) << std::endl;
    *this = std::move(out); // Number(std::move(caries));
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
    for (
        usize i = std::max(other.numbers.size(), numbers.size())-1;
        i > 0;
        --i
    ){
        if (i >= other.numbers.size() && numbers[i]){
            return false ^ xr;
        } else if (i >= numbers.size() && other.numbers[i])
            return true ^ xr;
        else if (i < numbers.size() && i < other.numbers.size()
            && numbers[i] < other.numbers[i]
        ){
            return true ^ xr;
        } else if (i < numbers.size() && i < other.numbers.size()
            && numbers[i] > other.numbers[i]
        )
            return false ^ xr;
    }
    if (numbers.size() == 0)
        return (0 < other.numbers[0]) ^ xr;
    if (other.numbers.size() == 0)
        return (numbers[0] < 0) ^ xr;
    return (numbers[0] < other.numbers[0]) ^ xr;
}

bool Number::operator >= (const Number & other) const {
    return !(*this < other);
}
bool Number::operator > (const Number & other) const {
    return (other < *this);
}
bool Number::operator <= (const Number & other) const {
    return !(*this > other);
}

bool Number::operator == (const Number & other) const {
    if (is_negative != other.is_negative) return false;
    // if (numbers.size() != other.numbers.size()) return false;
    for (usize i = 0; i < numbers.size(); ++i){
        if (numbers[i] != other.numbers[i]) return false;
    }
}


Number & Number::operator-=(const Number & other) {
    if (other.is_negative ^ is_negative) return operator +=(-other);
    bool swap = false;
    const Number & a = (*this > other) ? *this : other;
    const Number & b = (*this <= other) ? (swap = true, *this) : other;
    u32 borrow = 0;
    std::vector<u32> result;
    for (usize i = 0; i < a.numbers.size(); i++) {
        u32 diff = a.numbers[i] - borrow;
        if (i < b.numbers.size()) {
            diff -= b.numbers[i];
        }
        if (diff > a.numbers[i]) {
            borrow = 1;
            // diff += (1ULL << 32);
        } else {
            borrow = 0;
        }
        result.push_back(diff);
    }

    remove_leading_zeros(result);

    *this = Number(result, is_negative ^ swap);
    return *this;
}

Number Number::operator-(const Number & a) const{
    return Number(*this) -= a;
}

Number Number::operator-() const{
    if (is_zero()) return *this;
    Number tmp(*this);
    tmp.is_negative = !tmp.is_negative;
    return tmp;
}

Number Number::operator / (const Number & divider) const {
    return divide(*this, divider).first;
}

Number Number::operator % (const Number & divider) const {
    return divide(*this, divider).second;
}

Number & Number::operator /= (const Number & divider){
    *this = *this / divider;
    return *this;
}

Number & Number::operator %= (const Number & divider){
    *this = *this % divider;
    return *this;
}

u32 find_digit(const Number & a, const Number & b){
    u32 digit = (1 << 30);
    u32 step = digit;
    while (!(b * digit <= a && b*(digit+1) > a)){
        step >>= 1;
        if (!step) step = 1;
        if (b * digit > a){
            digit -= step;
        } else digit += step;
    }
    return digit;
}

std::pair<Number,Number> Number::divide (Number upper, const Number & lower) {
    bool out_is_negative = upper.is_negative ^ lower.is_negative;

    if (lower.is_zero()) throw std::logic_error("division by zero");


    
    std::vector<u32> out_digits;

    while (upper >= lower){
        std::vector<u32> top_digits;
        for (
            usize i = upper.numbers.size() - 1;
            Number(top_digits) < lower && top_digits.size() != upper.numbers.size();
            --i)
        {
            top_digits.insert(top_digits.begin(), upper.numbers[i]);
        }
        u32 digit = find_digit(top_digits, lower);
        std::vector<u32> greater{1};
        for (usize i = 0; i < upper.numbers.size() - top_digits.size(); ++i)
            greater.emplace(greater.begin(), 0);
        upper -= (lower * digit * greater);
        out_digits.insert(out_digits.begin(), digit);
    }

    remove_leading_zeros(out_digits);

    return std::make_pair<Number, Number>(Number(out_digits), std::move(upper));

    Number rem = upper.abs();
    Number out(0);
    while (rem >= lower.abs()){
        rem -= lower.abs();
        out += 1;
    }
    out.is_negative = out_is_negative;
    return std::make_pair(out, rem);
}

// u32 Number::find_digit (Number upper, const Number & lower){
//     u32 num = 0;
//     while (upper > lower){
        
//     }
// }

bool Number::is_zero() const {
    for (const auto & i: numbers){
        if (i)
            return false;
    }
    return true;
}

Number Number::abs() const {
    return Number(numbers, false);
}

Number * Number::clone() const {
    return new Number(*this);
}

Number::Number(const std::string & num): numbers{(u32)std::stoi(num)} {}

Number Number::operator>>(u32 shift) const{
    return Number(*this) >>= shift;
}

Number & Number::operator>>=(u32 shift) {
    if (shift > 32) exit(1);
    for (usize i = 0; i < numbers.size() - 1; ++i){
        u64 tmp = numbers[i] | ((u64)numbers[i+1] << 32);
        tmp >>= shift;
        numbers[i] = tmp;
    }

    // Remove leading zeros
    while (numbers.size()-1 && !numbers.back()){
        numbers.pop_back();
    }
    return *this;
}