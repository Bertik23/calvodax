#pragma once

#include "astnode.h"

class UnOp : public ASTNode{
public:
    UnOp(const ASTNode & arg);
    // ~UnOp() override;
    // UnOp(const UnOp &);
    // UnOp & operator = (const UnOp &);
protected:
    std::shared_ptr<ASTNode> arg;
};

