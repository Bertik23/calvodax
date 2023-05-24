#include "asignbinop.h"

AsignBinOp * AsignBinOp::clone() const {
    return new AsignBinOp(*this);
}

std::shared_ptr<Rational> AsignBinOp::eval(Context & cntx) const {
    auto var = lhs->eval(cntx);
    *var = *rhs->eval(cntx);
    return var;
}

void AsignBinOp::print(std::ostream & os) const {
    os << "(= " << *lhs << " " << *rhs << ")";
}