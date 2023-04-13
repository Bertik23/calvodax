#include "integer.h"

class Rational : public Number {
private:
    void simplify();
    Integer numerator; // The upper number
    Integer denominator; // The lower number
};
