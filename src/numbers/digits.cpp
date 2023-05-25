#include "digits.h"

#include <cmath>
#include <iomanip>
#include <bitset>
#include <regex>

void remove_leading_zeros(std::vector<u32> & arr){
    while (arr.size() > 1 && !arr.back()){
        arr.pop_back();
    }
}


std::ostream & operator << (std::ostream & os, const Digits & n){
    n.print(os);
    return os;
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

    if (os.flags() & os.hex){
        os << "0x";
        usize i = 0;
        for (auto it = numbers.rbegin(); it != numbers.rend(); ++it){
            if (i) os << std::setw(8) << std::setfill('0');
            if (i || *it != 0) ++i;
            else continue;
            os << /* std::setw(8) << */ *it;
        }
        return;
    }
    if (os.flags() & os.dec)
        print_rec(os, *this);
}

void Digits::print_rec(std::ostream & os, const Digits & x){
    if ( x < 10 )
    {
        os << x.numbers[0];
        return;
    }

    auto o = divide(x, 10);
    os << o.first;
    os << o.second;
}

Digits & Digits::operator *= (const Digits & other){
    u32 cary = 0;
    is_negative = is_negative ^ other.is_negative;
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
            u64 o = (u64)other.numbers[j] * (u64)numbers[i];

            o_vec.push_back(o & (((u64)1<<33) - 1));
            cary = o >> 32;
            caries.push_back(cary);
        }
        out += caries;
        out += o_vec;
    }
    out.is_negative = is_negative;
    *this = std::move(out);
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
        return true ^ xr;
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
    if (is_zero() && other.is_zero()) return true;
    if (is_negative != other.is_negative) return false;
    if (numbers.size() != other.numbers.size()) return false;
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
    u32 digit = (1 << 31);
    u32 step = digit;
    Digits r;
    while (r = b*digit, !(r <= a && r+b > a)){
        step >>= 1;
        if (!step) step = 1;
        if (r > a){
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
        usize num_digits = upper.size();
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
        if (upper.is_zero() && top_digits.size() != num_digits){
            for (usize i = 0; i < num_digits - top_digits.size(); ++i){
                out_digits.emplace(out_digits.begin(), 0);
            }
        }
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

Digits Digits::from_hex_str(const std::string & str){
    Digits out(0);
    Digits order(1);
    usize pos = 0;
    // Check if there is a sign in front, if yes, set pos to 1 and adjust sign
    // of output acordingly
    if (str.front() == '+')
        out.is_negative = (++pos, false);
    else if (str.front() == '-')
        out.is_negative = ++pos;
    // Read chars from end, stop 2 or 3, if there is not a sign or if there is
    // a sign respectively, chars before begining (expects 0x prefix)
    for (auto it = str.rbegin(); it != str.rend()-2-pos; ++it){
        // C doesn't have if expresions, so ternary operators it is
        out += order * (
            *it >= 'a' && *it <= 'f'
                ? *it - 'a' + 0xa
                :
            (*it >= 'A' && *it <= 'F'
                ? *it - 'A' + 0xA
                : *it - '0'));
        order *= 0x10;        
    }
    return out;
}

Digits Digits::from_str(const std::string & s){
    if (std::regex_match(s, std::regex("[-+]?0x[0-9A-Fa-f]+"))){
        return from_hex_str(s);
    }
    return from_dec_str(s);
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