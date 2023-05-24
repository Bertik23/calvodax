#pragma once

#include "astnode.h"

class Export: public ASTNode{
public:
    Export(const std::string &);
    ~Export() override;
    std::shared_ptr<Rational> eval(Context &) const override;
    Export * clone() const override;
    void print(std::ostream &) const override;
private:
    std::string file;
};

