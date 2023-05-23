#include "sparse.h"

Sparse::Sparse(const Digits & digits): is_negative(digits.negative()){
    auto bits = digits.as_bits();
    usize i = 0;
    for (
        auto it = bits.begin();
        it != bits.end();
        ++it
    ){
        auto bit = *it;
        if (bit){
            ones.push_back(i);
        }
        ++i;
    }
}

Digits Sparse::get_digits() const {
    Digits out(0);
    for (auto & o: ones){
        std::cerr << o << std::endl;
        out += Digits(2).power(o);
    }
    if (is_negative) return -out;
    return out;
}

void Sparse::print(std::ostream & os) const {
    if (!ones.size()){
        os << "0";
        return;
    }
    if (is_negative) os << "-";
    bool is_first = true;
    for (auto & o: ones){
        if (!is_first)
            os << "+";
        is_first -= 1;
        os << "2^" << o;
    }
}

usize Sparse::get_size() const {
    return ones.size() * 8;
}