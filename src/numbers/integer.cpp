#include "integer.h"

Integer::Integer(const std::string & str)
    : number(find_representation(Digits::from_dec_str(str))) {}

Integer::Integer(i32 i)
    : number(find_representation(Digits(i))) {}

Integer::Integer(Digits i)
    : number(find_representation(i)) {}

Integer & Integer::operator += (const Integer & other){
    number = find_representation(number->get_digits() + other.number->get_digits());
    return *this;
}


Integer & Integer::operator -= (const Integer & other){
    number = find_representation(number->get_digits() - other.number->get_digits());
    return *this;

}
Integer & Integer::operator *= (const Integer & other){
    number = find_representation(number->get_digits() * other.number->get_digits());
    return *this;
}
Integer & Integer::operator /= (const Integer & other){
    number = find_representation(number->get_digits() / other.number->get_digits());
    return *this;
}
Integer & Integer::operator %= (const Integer & other){
    number = find_representation(number->get_digits() % other.number->get_digits());
    return *this;
}

Integer Integer::operator + (const Integer & other) const {
    return Integer(*this) += other;
}

Integer Integer::operator - (const Integer & other) const {
    return Integer(*this) -= other;
}

Integer Integer::operator * (const Integer & other) const{
    return Integer(*this) *= other;
}
//Integer Integer::operator - () const{
    //return ;
//}
Integer Integer::operator / (const Integer & other) const{
    return Integer(*this) /= other;
}
Integer Integer::operator % (const Integer & other) const{
    return Integer(*this) %= other;
}


bool Integer::operator < (const Integer & other) const{
    return number->get_digits() < other.number->get_digits();
}
bool Integer::operator <= (const Integer & other) const{
    return number->get_digits() <= other.number->get_digits();
}
bool Integer::operator > (const Integer & other) const{
    return number->get_digits() > other.number->get_digits();
}
bool Integer::operator >= (const Integer & other) const{
    return number->get_digits() >= other.number->get_digits();
}
bool Integer::operator == (const Integer & other) const{
    return number->get_digits() == other.number->get_digits();
}

bool Integer::is_zero() const {
    return number->get_digits().is_zero();
}

void Integer::print(std::ostream & os) const {
    return number->print(os);
}

Integer * Integer::clone () const {
    return new Integer(*this);
}

Integer Integer::power(const Integer & other) const {
    if (other.is_zero()) return 1;
    if (other == 1) return *this;
    auto div = Digits::divide(other.number->get_digits(), 2);
    if (div.second.is_zero()){
        auto mid = power(div.first);
        return mid * mid;
    }
    return *this * power(other - 1);
} 

std::pair<Integer, Integer> Integer::divide(
    const Integer & a, const Integer & b
){
    auto div = Digits::divide(a.number->get_digits(), b.number->get_digits());
    return std::pair<Integer, Integer>(
        std::move(div.first), std::move(div.second)
    );
}