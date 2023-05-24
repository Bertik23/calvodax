#include "minusbinop.h"

std::shared_ptr<Rational> MinusBinOp::eval(Context & cntx) const{
    return std::shared_ptr<Rational>((*lhs->eval(cntx) - *rhs->eval(cntx)).clone());
}

MinusBinOp * MinusBinOp::clone() const{
    return new MinusBinOp(*this);
}

void MinusBinOp::print(std::ostream & os) const {
    os << "(- " << *lhs << " " << *rhs << ")";
}
