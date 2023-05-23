#include "integer.h"

Integer::Integer(const std::string & str)
    : number(find_representation(Digits(std::stoi(str)))) {}

Integer::Integer(i32 i)
    : number(find_representation(Digits(i))) {}

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