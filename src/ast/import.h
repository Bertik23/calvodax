#pragma once

#include "astnode.h"

class Import: public ASTNode{
public:
    Import(const std::string &);
    ~Import() override;
    std::shared_ptr<Rational> eval(Context &) const override;
    Import * clone() const override;
    void print(std::ostream &) const override;
private:
    std::string file;
};
