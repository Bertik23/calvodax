/** @file */
#pragma once

#include "binop.h"

class DivideBinOp: public BinOp{
public:
    using BinOp::BinOp;
    /**
     * Evaluates node.
     * 
     * @throw `text_error` on invalid operations
    */
    std::shared_ptr<Rational> eval(Context &) const override;
    DivideBinOp * clone() const override;
    void print(std::ostream &) const override;
};