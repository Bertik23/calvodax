#include "dense.h"

Dense::Dense(const Digits & digits): digits(digits) {}

Digits Dense::get_digits() const {
    return digits;
}