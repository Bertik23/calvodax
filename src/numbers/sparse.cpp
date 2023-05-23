#include "sparse.h"

Sparse::Sparse(const Digits & digits){
    auto bits = digits.as_bits();
    for (
        usize k = 0, i = bits.size()-1;
        k < bits.size();
        ++k, i = bits.size() - 1 - k
    ){
        if (bits[i]){
            ones.push_back(i);
        }
    }
}

Digits Sparse::get_digits() const {
    Digits out(0);
    for (auto & o: ones){
        out += Digits(2).power(o);
    }
    return out;
}

void Sparse::print(std::ostream & os) const {
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