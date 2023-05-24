#include "timesbinop.h"

std::shared_ptr<Rational> TimesBinOp::eval(Context & cntx) const{
    //std::cerr << "Times" << std::endl; 
    auto out = std::shared_ptr<Rational>((*lhs->eval(cntx) * *rhs->eval(cntx)).clone());
    //std::cerr << "Times end" << std::endl;
    return out;
}

TimesBinOp * TimesBinOp::clone() const{
    return new TimesBinOp(*this);
}

void TimesBinOp::print(std::ostream & os) const {
    os << "(* " << *lhs << " " << *rhs << ")";
}
