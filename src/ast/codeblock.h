/** @file */
#pragma once

#include "astnode.h"

class CodeBlock : public ASTNode {
public:
    CodeBlock();
    ~CodeBlock() override = default;
    /**
     * Evaluates node.
     * 
     * @throw `text_error` on invalid operations
    */
    std::shared_ptr<Rational> eval(Context &) const override;
    CodeBlock * clone() const override;
    void print(std::ostream &) const override;   
    void add_expr(std::shared_ptr<ASTNode>);
protected:
    std::vector<std::shared_ptr<ASTNode>> expresions;
};
