/** @file */
#pragma once

#include "astnode.h"

/**
 * Node for holding the export command.
*/
class Export: public ASTNode{
public:
    /**
     * Constucts node with file name.
    */
    Export(const std::string &);
    ~Export() override;
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
    Export * clone() const override;
    /**
     * Prints self to output stream.
    */
    void print(std::ostream &) const override;
private:
    std::string file;
};

