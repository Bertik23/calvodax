/** @file */
#pragma once

#include "astnode.h"

/**
 * Abstract node for holding a binary operator.
*/
class BinOp : public ASTNode{
public:
    /**
     * Constructs binary operator node with lhs and rhs.
    */
    BinOp(const ASTNode & lhs, const ASTNode & rhs);
protected:
    std::shared_ptr<ASTNode> lhs;
    std::shared_ptr<ASTNode> rhs;
};


