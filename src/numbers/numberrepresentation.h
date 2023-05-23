#pragma once

#include "digits.h"
#include <memory>
#include <iostream>


class NumberRepresentation{
public:
    virtual ~NumberRepresentation() = default;
    virtual Digits get_digits() const = 0;
    virtual void print(std::ostream &) const = 0;
};

std::shared_ptr<NumberRepresentation> find_representation(const Digits &);