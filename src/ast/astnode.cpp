#include "astnode.h"

std::ostream & operator << (std::ostream & os, const ASTNode & ast){
    ast.print(os);
    return os;
}
