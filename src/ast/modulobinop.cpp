#include "modulobinop.h"

std::shared_ptr<Rational> ModuloBinOp::eval(Context & cntx) const{
    return std::shared_ptr<Rational>((*lhs->eval(cntx) % (*rhs->eval(cntx))).clone());
}

void ModuloBinOp::print(std::ostream & os) const {
    os << "(^ " << *lhs << " " << *rhs << ")";
}

ModuloBinOp * ModuloBinOp::clone() const{
    return new ModuloBinOp(*this);
}
