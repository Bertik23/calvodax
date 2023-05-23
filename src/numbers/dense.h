#pragma once

#include "numberrepresentation.h"

class Dense : public NumberRepresentation {
public:
    Dense(const Digits &);
    Digits get_digits() const override;
    void print(std::ostream &) const override;
protected:
    Digits digits;
};