/** @file */
#pragma once

#include "numberrepresentation.h"

#include <vector>

#include "integer.h"

/**
 * Sparse numbers that have few 1 in their binary representation.
*/
class Sparse : public NumberRepresentation {
public:
    Sparse(const Digits &);
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
    /**
     * Indexes with ones in binary representation.
    */
    std::vector<usize> ones;
    bool is_negative;
};