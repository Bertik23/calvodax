/** @file */
#pragma once

#include "astnode.h"

/**
 * Node for holding a variable.
*/
class Var : public ASTNode{
public:
    /**
     * Constructs node with name.
    */
    Var(const std::string &);
    ~Var() override;
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
    Var * clone() const override;
    /**
     * Prints self to output stream.
    */
    void print(std::ostream &) const override;
private:
    std::string name;
};