/** @file */
#pragma once

#include "digits.h"
#include <memory>
#include <iostream>

/**
 * Abstract base class for all number representations.
*/
class NumberRepresentation{
public:
    virtual ~NumberRepresentation() = default;
    /**
     * Returns digits stored.
    */
    virtual Digits get_digits() const = 0;
    virtual void print(std::ostream &) const = 0;
    /**
     * Returns size in bytes.
    */
    virtual usize get_size() const = 0;
};

/**
 * Chooses the best number representation from Digits.
 * 
 * Constructs all of them and uses the with minimal size.
*/
std::shared_ptr<NumberRepresentation> find_representation(const Digits &);