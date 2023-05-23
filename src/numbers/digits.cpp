#include "digits.h"

#include <cmath>
#include <iomanip>
#include <bitset>

#define HEX

void remove_leading_zeros(std::vector<u32> & arr){
    while (arr.size() > 1 && !arr.back()){
        arr.pop_back();
    }
}

Digits::Digits(): numbers(), is_negative(false){};

Digits::Digits(i32 i)
    : numbers{(u32) std::abs(i)},
      is_negative(i < 0){}

Digits::Digits(u32 i)
    : numbers{i},
      is_negative(false){}

Digits::Digits(u64 i)
    : numbers{(u32)i, (u32)(i >> 32)},
      is_negative(false) {};

Digits::~Digits() = default;

Digits::Digits(const Digits & o) = default;
Digits::Digits(Digits && o) = default;
Digits & Digits::operator = (const Digits &) = default;
Digits & Digits::operator = (Digits &&) = default;

Digits::Digits(const std::vector<u32> & v, bool is_negative = false)
  : numbers(v), is_negative(is_negative) {
    remove_leading_zeros(numbers);
  }
Digits::Digits(std::vector<u32> && v, bool is_negative = false)
  : numbers(std::move(v)), is_negative(is_negative) {
    remove_leading_zeros(numbers);
  }

Digits & Digits::operator += (const Digits & other){
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

Digits Digits::operator + (const Digits & other) const{
    Digits tmp(*this);
    return tmp += other;
}

/**
 * Print big int
*/
void Digits::print(std::ostream & os) const {
    if (is_zero()) {
        os << "0";
        return;
    }
    if (is_negative){
        os << "-";
    }
    if (os.hex){
        usize i = 0;
        for (auto it = numbers.rbegin(); it != numbers.rend(); ++it){
            if (i) os << std::setw(8) << std::setfill('0');
            if (i || *it != 0) ++i;
            else continue;
            os << /* std::setw(8) << */ *it;
        }
        return;
    }
    if (os.dec)
        print_rec(os, *this);
}

void Digits::print_rec(std::ostream & os, const Digits & x){
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

Digits & Digits::operator *= (const Digits & other){
    u32 cary = 0;
    //std::cerr << is_negative << " " << other.is_negative << " ";
    is_negative = is_negative ^ other.is_negative;
    //std::cerr << is_negative << std::endl;
    if (is_zero() || other.is_zero()){
        is_negative = false;
        numbers = {0};
        return *this;
    }
    Digits out{0};
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
    out.is_negative = is_negative;
    // std::cout << "Digits: " << Digits(caries) << std::endl;
    *this = std::move(out); // Digits(std::move(caries));
    return *this;
}

Digits Digits::operator * (const Digits & other) const{
    Digits tmp(*this);
    return tmp *= other;
}

bool Digits::operator < (const Digits & other) const {
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

bool Digits::operator >= (const Digits & other) const {
    return !(*this < other);
}
bool Digits::operator > (const Digits & other) const {
    return (other < *this);
}
bool Digits::operator <= (const Digits & other) const {
    return !(*this > other);
}

bool Digits::operator == (const Digits & other) const {
    if (is_negative != other.is_negative) return false;
    // if (numbers.size() != other.numbers.size()) return false;
    for (usize i = 0; i < numbers.size(); ++i){
        if (numbers[i] != other.numbers[i]) return false;
    }
    return true;
}


Digits & Digits::operator-=(const Digits & other) {
    if (other.is_negative ^ is_negative) return operator +=(-other);
    bool swap = false;
    const Digits & a = (*this > other) ? *this : other;
    const Digits & b = (*this <= other) ? (swap = true, *this) : other;
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

    *this = Digits(result, is_negative ^ swap);
    return *this;
}

Digits Digits::operator-(const Digits & a) const{
    return Digits(*this) -= a;
}

Digits Digits::operator-() const{
    if (is_zero()) return *this;
    Digits tmp(*this);
    tmp.is_negative = !tmp.is_negative;
    return tmp;
}

Digits Digits::operator / (const Digits & divider) const {
    return divide(*this, divider).first;
}

Digits Digits::operator % (const Digits & divider) const {
    return divide(*this, divider).second;
}

Digits & Digits::operator /= (const Digits & divider){
    *this = *this / divider;
    return *this;
}

Digits & Digits::operator %= (const Digits & divider){
    *this = *this % divider;
    return *this;
}

u32 find_digit(const Digits & a, const Digits & b){
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

std::pair<Digits,Digits> Digits::divide (Digits upper, const Digits & lower) {
    bool out_is_negative = upper.is_negative ^ lower.is_negative;

    if (lower.is_zero()) throw std::logic_error("division by zero");

    if (lower == 2){
        return std::pair<Digits, Digits>(upper >> 1, upper.numbers[0] & 1);
    }
    
    std::vector<u32> out_digits;

    while (upper >= lower){
        std::vector<u32> top_digits;
        for (
            usize i = upper.numbers.size() - 1;
            Digits(top_digits) < lower && top_digits.size() != upper.numbers.size();
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

    return std::make_pair<Digits, Digits>(Digits(out_digits), std::move(upper));

    Digits rem = upper.abs();
    Digits out(0);
    while (rem >= lower.abs()){
        rem -= lower.abs();
        out += 1;
    }
    out.is_negative = out_is_negative;
    return std::make_pair(out, rem);
}

// u32 Digits::find_digit (Digits upper, const Digits & lower){
//     u32 num = 0;
//     while (upper > lower){
        
//     }
// }

bool Digits::is_zero() const {
    for (const auto & i: numbers){
        if (i)
            return false;
    }
    return true;
}

Digits Digits::abs() const {
    return Digits(numbers, false);
}

Digits * Digits::clone() const {
    return new Digits(*this);
}

Digits::Digits(const std::string & num): numbers{(u32)std::stoi(num)} {}

Digits Digits::operator>>(u32 shift) const{
    return Digits(*this) >>= shift;
}

Digits & Digits::operator>>=(u32 shift) {
    if (shift > 32) exit(1);
    for (usize i = 0; i < numbers.size() - 1; ++i){
        u64 tmp = (u64)numbers[i] | ((u64)numbers[i+1] << 32);
        tmp >>= shift;
        numbers[i] = tmp;
    }
    numbers.back() >>= shift;

    remove_leading_zeros(numbers);
    return *this;
}

Digits Digits::from_dec_str(const std::string & str){
    Digits out(0);
    Digits order(1);
    for (auto it = str.rbegin(); it != str.rend(); ++it){
        if (*it == '+') continue;
        else if (*it == '-'){
            out.is_negative = true;
            continue;
        }
        out += order * (*it - '0');
        order *= 10;
    }
    return out;
}

std::vector<bool> Digits::as_bits() const {
    std::vector<bool> out;
    for(auto it = numbers.begin(); it != numbers.end(); ++it){
        auto bits = std::bitset<32>(*it);
        for (usize i = 0; i < 32; ++i){
            out.push_back(bits[i]);
        }
    }
    return out;
}


Digits Digits::power(const Digits & other) const {
    if (other.is_zero()) return 1;
    if (other == 1) return *this;
    auto div = Digits::divide(other, 2);
    if (div.second.is_zero()){
        auto mid = power(div.first);
        return mid * mid;
    }
    return *this * power(other - 1);
}

usize Digits::size() const {
    return numbers.size();
}

bool Digits::negative() const {
    return is_negative;
}