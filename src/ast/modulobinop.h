/** @file */
#pragma once

#include "binop.h"

/**
 * Node for holding the modulo binary operator.
*/
class ModuloBinOp: public BinOp{
public:
    using BinOp::BinOp;
    /**
     * Evaluates node.
     * 
     * @throw `text_error` on invalid operations
    */
    std::shared_ptr<Rational> eval(Context &) const override;
    /**
     * Uses copyconstructor to make a heap allocated copy of self and return
     * pointer to it.
    */
    ModuloBinOp * clone() const override;
    /**
     * Prints self to output stream.
    */
    void print(std::ostream &) const override;
};
