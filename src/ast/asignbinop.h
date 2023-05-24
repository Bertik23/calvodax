#pragma once

#include "astnode.h"

#include "binop.h"

class AsignBinOp: public BinOp{
public:
    using BinOp::BinOp;
    std::shared_ptr<Rational> eval(Context &) const override;
    AsignBinOp * clone() const override;
    void print(std::ostream &) const override;
};
