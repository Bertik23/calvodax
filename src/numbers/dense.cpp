#include "dense.h"

Dense::Dense(const Digits & digits): digits(digits) {}

Digits Dense::get_digits() const {
    return digits;
}

void Dense::print(std::ostream & os) const {
    digits.print(os);
}

usize Dense::get_size() const {
    return digits.size() * 4;
}