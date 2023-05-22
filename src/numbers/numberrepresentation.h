#pragma once

#include "digits.h"
#include <memory>


class NumberRepresentation{
public:
    virtual ~NumberRepresentation() = default;
    virtual Digits get_digits() const = 0;
};

std::shared_ptr<NumberRepresentation> find_representation(const Digits &);