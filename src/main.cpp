#include "numbers/number.h"
#include <cassert>

#include <iostream>

using namespace std;

int main(){
    Number a((1LL << 31) - 1);
    Number b(20);

    cout << a << endl;

    cout << a + a + a + a + a + a + a + a << endl;

    cout << "2^31 - 1 × 2^31 - 1" << endl;
    cout << a * a << endl;

    Number c(0);
    Number d(-1);

    cout << "0 × 0" << endl;
    cout << ">>> " << c * c << endl;
    cout << "-1 × -1" << endl;
    cout << ">>> " << d * d << endl;
    cout << "0 × 20" << endl;
    cout << ">>> " << c * b << endl;
    cout << "0 × -1" << endl;
    cout << ">>> " << c * d << endl;

    assert(Number(1) < Number(2));
    assert(Number(0) < Number(1));
    assert(!(Number(1) < Number(0)));
    assert(Number(-1) < Number(1));
}
