#include "codeblock.h"

CodeBlock::CodeBlock(): expresions() {};

std::shared_ptr<Rational> CodeBlock::eval(Context & cntx) const {
    if (expresions.size() == 0) return std::shared_ptr<Rational>(new Rational(0));

    for (auto it = expresions.begin(); it != expresions.end()-1; ++it){
        (*(*it)).eval(cntx);
    }
    return expresions.back()->eval(cntx);
}

CodeBlock * CodeBlock::clone() const {
    return new CodeBlock(*this);
}

void CodeBlock::print(std::ostream & os) const {
    os << "(CodeBlock\n";
    for(auto & expr: expresions){
        expr->print(os);
        os << "\n";
    }
    os << ")";
}   

void CodeBlock::add_expr(std::shared_ptr<ASTNode> ast){
    expresions.emplace_back(ast);
}
