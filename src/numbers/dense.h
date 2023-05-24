/** @file */
#pragma once

#include "numberrepresentation.h"

/**
 * Basic number representation, stored in raw digits.
*/
class Dense : public NumberRepresentation {
public:
    Dense(const Digits &);
    /**
     * Returns digits stored.
    */
    Digits get_digits() const override;
    void print(std::ostream &) const override;
    /**
     * Returns size in bytes.
    */
    usize get_size() const override;
protected:
    Digits digits;
};