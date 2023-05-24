#include "unop.h"

UnOp::UnOp(const ASTNode & arg): arg(arg.clone()){}