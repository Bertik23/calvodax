#pragma once

#include "binop.h"

class ModuloBinOp: public BinOp{
public:
    using BinOp::BinOp;
    std::shared_ptr<Rational> eval(Context &) const override;
    ModuloBinOp * clone() const override;
    void print(std::ostream &) const override;
};
