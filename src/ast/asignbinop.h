/** @file */
#pragma once

#include "astnode.h"

#include "binop.h"

/**
 * Node for holding the assignment binary operator.
*/
class AsignBinOp: public BinOp{
public:
    using BinOp::BinOp;
    /**
     * @brief Evaluates node.
     * 
     * @throw `text_error` on invalid operations
    */
    std::shared_ptr<Rational> eval(Context &) const override;
    /**
     * Uses copyconstructor to make a heap allocated copy of self and return
     * pointer to it.
    */
    AsignBinOp * clone() const override;
    /**
     * Prints self to output stream.
    */
    void print(std::ostream &) const override;
};
