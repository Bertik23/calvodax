#include "powerbinop.h"

std::shared_ptr<Rational> PowerBinOp::eval(Context & cntx) const{
    return std::shared_ptr<Rational>((lhs->eval(cntx)->power(*rhs->eval(cntx))).clone());
}

void PowerBinOp::print(std::ostream & os) const {
    os << "(^ " << *lhs << " " << *rhs << ")";
}

PowerBinOp * PowerBinOp::clone() const{
    return new PowerBinOp(*this);
}