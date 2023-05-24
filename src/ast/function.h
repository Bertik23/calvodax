#pragma once

#include "astnode.h"
#include "codeblock.h"

class Function : public CodeBlock {
public:
    Function(const std::string &);
    std::shared_ptr<Rational> eval(Context &) const override;
    Function * clone() const override;
    void print(std::ostream &) const override;
protected:
    std::string name;
};
