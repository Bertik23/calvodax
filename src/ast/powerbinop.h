#pragma once

#include "binop.h"

class PowerBinOp: public BinOp{
public:
    using BinOp::BinOp;
    std::shared_ptr<Rational> eval(Context &) const override;
    PowerBinOp * clone() const override;
    void print(std::ostream &) const override;
};
