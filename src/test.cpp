#include "numbers/rational.h"
#include "numbers/integer.h"
#include <iostream>

using namespace std;

int main(){
    cout << Rational(2000, 2) << endl;
    cout << (Integer(1) == Integer(1)) << endl;
    cout << Integer(5).power(Integer(2)) << endl;
    cout << Rational(5).power(Rational(2)) << endl;
}
