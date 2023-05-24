#pragma once

#include "astnode.h"

class BinOp : public ASTNode{
public:
    BinOp(const ASTNode & lhs, const ASTNode & rhs);
protected:
    std::shared_ptr<ASTNode> lhs;
    std::shared_ptr<ASTNode> rhs;
};


