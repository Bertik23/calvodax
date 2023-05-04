#include "numbers/number.h"

#include <iostream>

using namespace std;

int main(){
    Number a((1LL << 63) - 1);
    Number b(20);

    cout << a << endl;

    cout << a + a + a + a + a + a + a + a << endl;
}
