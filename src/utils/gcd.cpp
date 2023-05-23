#include "gcd.h"

Integer gcd(const Integer & a, const Integer & b){
    if (a == Integer(1) || b == Integer(1))
        return 1;
    if (b.is_zero())
        return a;
    return gcd(b, a % b);
}