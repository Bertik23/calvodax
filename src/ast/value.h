/** @file */
#pragma once

#include "astnode.h"

/**
 * Node for holding a literal value.
*/
class Value : public ASTNode{
public:
    /**
     * Constructs node with value from string input.
    */
    Value(const std::string &);
    ~Value() override;
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
    Value * clone() const override;
    /**
     * Prints self to output stream.
    */
    void print(std::ostream &) const override;
protected:
    std::shared_ptr<Rational> value;
};
