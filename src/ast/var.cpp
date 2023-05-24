#include "var.h"

Var::Var(const std::string & str): name(str) {}

Var::~Var() = default;

std::shared_ptr<Rational> Var::eval(Context & cntx) const {
    return cntx.variable_map.emplace(
        name, std::shared_ptr<Rational>(new Rational(0))
    ).first->second;
}

void Var::print(std::ostream & os) const {
    os << name;
}

Var * Var::clone() const {
    return new Var(*this);
}
