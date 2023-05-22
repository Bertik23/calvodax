#pragma once

#include "numberrepresentation.h"

class Dense : public NumberRepresentation {
public:
    Dense(const Digits &);
    Digits get_digits() const override;
protected:
    Digits digits;
};