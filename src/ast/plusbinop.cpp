#include "plusbinop.h"

std::shared_ptr<Rational> PlusBinOp::eval(Context & cntx) const{
    return std::shared_ptr<Rational>((*lhs->eval(cntx) + *rhs->eval(cntx)).clone());
}

PlusBinOp * PlusBinOp::clone() const{
    return new PlusBinOp(*this);
}

void PlusBinOp::print(std::ostream & os) const {
    os << "(+ " << *lhs << " " << *rhs << ")";
}