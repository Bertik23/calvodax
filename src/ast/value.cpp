#include "value.h"

Value::Value(const std::string & num): value(new Rational(num)) {};

std::shared_ptr<Rational> Value::eval(Context &) const {
    return value;
}

Value::~Value() = default;

Value * Value::clone() const {
    return new Value(*this);
}

void Value::print(std::ostream & os) const {
    os << *value;
}
