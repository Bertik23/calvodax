#include "function.h"

#include <unordered_map>
#include <functional>

#include "../utils/exceptions.h"

std::unordered_map<
    std::string,
    std::function<std::shared_ptr<Rational>(std::shared_ptr<Rational>)>
> FUNCTION_MAP {
    {"factorial", [](std::shared_ptr<Rational> in){
        std::shared_ptr<Rational> out(new Rational(1));
        for (Rational i(2); i <= *in; i+=Rational(1)){
            *out *= i;
        }
        return out;
    }},
    {"round", [](std::shared_ptr<Rational> in){
        return std::shared_ptr<Rational>(in->round().clone());
    }},
    {"floor", [](std::shared_ptr<Rational> in){
        return std::shared_ptr<Rational>(in->floor().clone());
    }},
    {"ceil", [](std::shared_ptr<Rational> in){
        return std::shared_ptr<Rational>(in->ceil().clone());
    }}
};


Function::Function(const std::string & name): CodeBlock(), name(name){};

std::shared_ptr<Rational> Function::eval(Context & cntx) const {
    auto f = FUNCTION_MAP.find(name);
    if (f == FUNCTION_MAP.end()){
        throw text_error("Undefined function: " + name);
    }
    return f->second(expresions.front()->eval(cntx));
}

Function * Function::clone() const {
    return new Function(*this);
}

void Function::print(std::ostream & os) const {
    os << "("+ name + " ";
    for(auto & expr: expresions){
        expr->print(os);
        os << " ";
    }
    os << ")";
}   