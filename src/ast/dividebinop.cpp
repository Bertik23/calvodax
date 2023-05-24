#include "dividebinop.h"

std::shared_ptr<Rational> DivideBinOp::eval(Context & cntx) const{
    return std::shared_ptr<Rational>((*lhs->eval(cntx) / *rhs->eval(cntx)).clone());
}

void DivideBinOp::print(std::ostream & os) const {
    os << "(/ " << *lhs << " " << *rhs << ")";
}

DivideBinOp * DivideBinOp::clone() const{
    return new DivideBinOp(*this);
}
