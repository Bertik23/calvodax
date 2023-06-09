#include <cassert>
#include <iostream>
#include <iomanip>

#include "numbers/integer.h"
#include "parser/tokenizer.h"
#include "parser/parser.h"
#include "utils/exceptions.h"
#include "parser/context.h"

using namespace std;

/**
 * Degug print to specified output stream.
*/
template<typename T>
ostream & dbg_os(ostream & os, const T & t){
    return os << "Debug: " << t << endl;
}

/**
 * Debug print to stderr
*/
template<typename T>
void dbg(const T & t){
    dbg_os<T>(cerr, t);
}

int main(){
    cout << hex;

    Context cntx;

    while (cin){
        cout << ">>> ";
        
        shared_ptr<ASTNode> ast;
        try {
            string line;
            std::getline(cin, line);
            if (line == "base16"){
                cout << hex;
                continue;
            }
            else if (line == "base10"){
                cout << dec;
                continue;
            }
            auto tokens = tokenize(line);
            ast = parse(tokens);
        } catch (syntax_error & e){
            cout << "Syntax error: " + string(e.what()) << endl;
            continue;
        } catch (exit_exception &){
            return 0;
        } catch (text_error & e){
            cout << "Error: " + string(e.what()) << endl;
            continue;
        }

        shared_ptr<Rational> eval;
        try {
            eval = ast->eval(cntx);
            cout << "<<< " << *eval << endl;
        } catch (text_error & e){
            cout << "Error: " + string(e.what()) << endl;
        } catch (std::logic_error & e){
            cout << "Error: " + string(e.what()) << endl;
        } catch(...){
            cout << "Unexpected error." << endl;
        }
    }

    return 0;
}
