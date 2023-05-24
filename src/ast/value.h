#pragma once

#include "astnode.h"

class Value : public ASTNode{
public:
    Value(const std::string &);
    ~Value() override;
    std::shared_ptr<Rational> eval(Context &) const override;
    Value * clone() const override;
    void print(std::ostream &) const override;
protected:
    std::shared_ptr<Rational> value;
};
