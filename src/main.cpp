#include "numbers/number.h"
#include <cassert>
#include "parser/tokenizer.h"
#include "parser/parser.h"

#include <iostream>

using namespace std;

int main(){
    auto tokens = tokenize(cin);
    for (const auto & a: tokens){
        cout << a << endl;
    }

    cout << "---------------\n";

    auto ast = parse(static_cast<std::list<Token>&>(tokens));

    cout << *ast << endl;

    cout << *ast->eval() << endl;


    return 0;
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



    cout << "\n\n--- PLUS ---\n" << endl; 

    cout << Number(10) + Number(10) << endl;
    cout << Number(-10) + Number(10) << endl;
    cout << Number(10) + Number(-10) << endl;
    cout << Number(10) + Number(-15) << endl;
    cout << Number(-10) + Number(-15) << endl;
    cout << Number(-10) + Number(15) << endl;


    cout << "\n\n--- MINUS ---\n" << endl; 

    cout << Number(10) - Number(5) << endl;
    cout << Number(10) - Number(-5) << endl;
    cout << Number(10) - Number(15) << endl;
    cout << Number(10) - Number(10) << endl;
    cout << Number(-10) - Number(10) << endl;
    cout << Number(10) - Number(-10) << endl;
    cout << Number(10) - Number(-15) << endl;
    cout << Number(-10) - Number(-15) << endl;
    cout << Number(-10) - Number(15) << endl;


    cout << "\n\n--- DIVISION ---\n" << endl; 

    cout << Number(10) / Number(10) << endl;
    cout << Number(-10) / Number(10) << endl;
    cout << Number(10) / Number(-10) << endl;
    cout << Number(-10) / Number(-10) << endl;
    cout << Number(100) / Number(10) << endl;

    cout << Number(1234) << endl;
}
