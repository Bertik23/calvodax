/** @file */
#pragma once

#include "astnode.h"

class Value : public ASTNode{
public:
    Value(const std::string &);
    ~Value() override;
    /**
     * Evaluates node.
     * 
     * @throw `text_error` on invalid operations
    */
    std::shared_ptr<Rational> eval(Context &) const override;
    Value * clone() const override;
    void print(std::ostream &) const override;
protected:
    std::shared_ptr<Rational> value;
};
