/** @file */
#pragma once

#include <memory>
#include <iostream>

#include "../parser/context.h"
#include "../numbers/rational.h"

/**
 * Abstract base class for all nodes in the AST.
*/
class ASTNode{
public:
    virtual ~ASTNode() = default;
    /**
     * Evaluates node.
     * 
     * @throw `text_error` on invalid operations
    */
    virtual std::shared_ptr<Rational> eval(Context &) const = 0;
    /**
     * Uses copyconstructor to make a heap allocated copy of self and return
     * pointer to it.
    */
    virtual ASTNode * clone() const = 0;
    /**
     * Prints self to output stream.
    */
    virtual void print(std::ostream &) const = 0;
};

/**
 * Overloaded operator << for printing
 * 
 * Uses print function to write node to output stream.
*/
std::ostream & operator << (std::ostream &, const ASTNode &);