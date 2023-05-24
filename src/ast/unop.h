/** @file */
#pragma once

#include "astnode.h"

/**
 * Abstract node for holding a unary operator.
*/
class UnOp : public ASTNode{
public:
    /**
     * Constructs node with argument.
    */
    UnOp(const ASTNode & arg);
    // ~UnOp() override;
    // UnOp(const UnOp &);
    // UnOp & operator = (const UnOp &);
protected:
    std::shared_ptr<ASTNode> arg;
};

