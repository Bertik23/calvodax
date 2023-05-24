#pragma once

#include "astnode.h"

class Var : public ASTNode{
public:
    Var(const std::string &);
    ~Var() override;
    std::shared_ptr<Rational> eval(Context &) const override;
    Var * clone() const override;
    void print(std::ostream &) const override;
private:
    std::string name;
};