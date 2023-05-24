#pragma once

#include "binop.h"

class DivideBinOp: public BinOp{
public:
    using BinOp::BinOp;
    std::shared_ptr<Rational> eval(Context &) const override;
    DivideBinOp * clone() const override;
    void print(std::ostream &) const override;
};