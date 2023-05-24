#include "binop.h"

BinOp::BinOp(const ASTNode & lhs, const ASTNode & rhs)
     : lhs(lhs.clone()), rhs(rhs.clone()){}