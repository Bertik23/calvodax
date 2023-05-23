#pragma once

#include "numberrepresentation.h"

#include <vector>

#include "integer.h"

class Sparse : public NumberRepresentation {
public:
    Sparse(const Digits &);
    Digits get_digits() const override;
    void print(std::ostream &) const override;
    usize get_size() const override;
protected:
    std::vector<usize> ones;
    bool is_negative;
};