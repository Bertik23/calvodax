/** @file */
#pragma once

#include "astnode.h"

/**
 * Node for holding the import command.
*/
class Import: public ASTNode{
public:
    /**
     * Constructs node with file name.
    */
    Import(const std::string &);
    ~Import() override;
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
    Import * clone() const override;
    /**
     * Prints self to output stream.
    */
    void print(std::ostream &) const override;
private:
    std::string file;
};
