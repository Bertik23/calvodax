#pragma once

#include "astnode.h"
#include "binop.h"


class MinusBinOp: public BinOp{
public:
    using BinOp::BinOp;
    std::shared_ptr<Rational> eval(Context &) const override;
    MinusBinOp * clone() const override;
    void print(std::ostream &) const override;
};