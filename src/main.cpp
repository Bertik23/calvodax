#include <cassert>
#include <iostream>
#include <iomanip>

#include "numbers/integer.h"
#include "parser/tokenizer.h"
#include "parser/parser.h"
#include "utils/exceptions.h"
#include "parser/context.h"

using namespace std;

template<typename T>
ostream & dbg_os(ostream & os, const T & t){
    return os << "Debug: " << t << endl;
}

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
            // for (const auto & a: tokens){
            //     cerr << a << endl;
            // }

            // cerr << "---------------\n";
            ast = parse(tokens);
        } catch (syntax_error & e){
            cout << "Syntax error: " + string(e.what()) << endl;
            continue;
        } catch (exit_exception &){
            // delete ast;
            return 0;
        } catch (text_error & e){
            cout << "Error: " + string(e.what()) << endl;
            continue;
        }

        //dbg(*ast);
        shared_ptr<Rational> eval;
        try {
            eval = ast->eval(cntx);
            cout << "<<< " << *eval << endl;
        } catch (text_error & e){
            cout << "Error: " + string(e.what()) << endl;
        } catch (std::logic_error & e){
            cout << "Error: " + string(e.what()) << endl;
        } catch(...){
            throw;
        }
    }

    return 0;
}
