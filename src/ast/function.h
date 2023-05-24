/** @file */
#pragma once

#include "astnode.h"
#include "codeblock.h"

/**
 * Node for holding a function call.
*/
class Function : public CodeBlock {
public:
    /**
     * Constructs node with function name.
    */
    Function(const std::string &);
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
    Function * clone() const override;
    /**
     * Prints self to output stream.
    */
    void print(std::ostream &) const override;
protected:
    std::string name;
};
