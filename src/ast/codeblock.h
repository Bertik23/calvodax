/** @file */
#pragma once

#include "astnode.h"

/**
 * Node for holding a code block.
*/
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
    /**
     * Uses copyconstructor to make a heap allocated copy of self and return
     * pointer to it.
    */
    CodeBlock * clone() const override;
    /**
     * Prints self to output stream.
    */
    void print(std::ostream &) const override;
    /**
     * Adds expresion to code block.
    */
    void add_expr(std::shared_ptr<ASTNode>);
protected:
    std::vector<std::shared_ptr<ASTNode>> expresions;
};
