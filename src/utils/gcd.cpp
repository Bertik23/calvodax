#include "gcd.h"

Integer gcd(const Integer & a, const Integer & b){
    if (a == 1 || b == 1)
        return 1;
    if (b == 0)
        return a;
    return gcd(b, a % b);
}