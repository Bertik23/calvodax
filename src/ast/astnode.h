#pragma once

#include <memory>
#include <iostream>

#include "../parser/context.h"
#include "../numbers/rational.h"

class ASTNode{
public:
    virtual ~ASTNode() = default;
    virtual std::shared_ptr<Rational> eval(Context &) const = 0;
    virtual ASTNode * clone() const = 0;
    virtual void print(std::ostream &) const = 0;
};


std::ostream & operator << (std::ostream &, const ASTNode &);