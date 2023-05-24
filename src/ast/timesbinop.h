#pragma once

#include "binop.h"

class TimesBinOp: public BinOp{
public:
    using BinOp::BinOp;
    std::shared_ptr<Rational> eval(Context &) const override;
    TimesBinOp * clone() const override;
    void print(std::ostream &) const override;
};
