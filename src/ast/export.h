/** @file */
#pragma once

#include "astnode.h"

class Export: public ASTNode{
public:
    Export(const std::string &);
    ~Export() override;
    /**
     * Evaluates node.
     * 
     * @throw `text_error` on invalid operations
    */
    std::shared_ptr<Rational> eval(Context &) const override;
    Export * clone() const override;
    void print(std::ostream &) const override;
private:
    std::string file;
};

