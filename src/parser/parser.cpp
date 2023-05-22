#include "parser.h"

#include <unordered_map>
#include <sstream>
#include <functional>

#include "../utils/exceptions.h"
#include "../utils/utils.h"


std::unordered_map<std::string, i32> OP_PRECEDENSE {
    {"=", 1},
    {"+", 10},
    {"-", 10},
    {"*", 20},
    {"/", 20},
    {"<", 5},
    {">", 5},
};

static std::unordered_map<std::string, std::shared_ptr<Number>> VARIABLE_MAP;
static std::unordered_map<
    std::string,
    std::function<std::shared_ptr<Number>(std::shared_ptr<Number>)>
> FUNCTION_MAP {{"factorial", [](std::shared_ptr<Number> in){
    std::shared_ptr<Number> out(new Number(1));
    for (Number i(2); i <= *in; i+=1){
        *out *= i;
    }
    return out;
}}};

// -----------------------------------------------------------------------------
// CodeBlock

std::shared_ptr<Number> CodeBlock::eval() const {
    if (expresions.size() == 0) return std::shared_ptr<Number>(new Number());

    for (auto it = expresions.begin(); it != expresions.end()-1; ++it){
        (*(*it)).eval();
    }
    return expresions.back()->eval();
}

CodeBlock * CodeBlock::clone() const {
    return new CodeBlock(*this);
}

void CodeBlock::print(std::ostream & os) const {
    os << "(CodeBlock\n";
    for(auto & expr: expresions){
        expr->print(os);
        os << "\n";
    }
    os << ")";
}   

void CodeBlock::add_expr(std::shared_ptr<ASTNode> ast){
    expresions.emplace_back(ast);
}

// -----------------------------------------------------------------------------
// Function

Function::Function(const std::string & name): CodeBlock(), name(name){};

std::shared_ptr<Number> Function::eval() const {
    auto f = FUNCTION_MAP.find(name);
    if (f == FUNCTION_MAP.end()){
        throw text_error("Undefined function: " + name);
    }
    return f->second(expresions.front()->eval());
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

// -----------------------------------------------------------------------------
// BinOp

BinOp::BinOp(const ASTNode & lhs, const ASTNode & rhs)
     : lhs(lhs.clone()), rhs(rhs.clone()){}

// BinOp::~BinOp(){
//    delete lhs;
//    delete rhs;
// }

//BinOp::BinOp(const BinOp & other)
    //: lhs(other.lhs->clone()),
      //rhs(other.rhs->clone())
    //{}

//BinOp & BinOp::operator = (const BinOp & other){
    //delete lhs;
    //delete rhs;
    //lhs = other.lhs->clone();
    //rhs = other.rhs->clone();
    //return *this;
//}

// -----------------------------------------------------------------------------
// UnOp

UnOp::UnOp(const ASTNode & arg): arg(arg.clone()){}

//UnOp::~UnOp(){
    //delete arg;
//}

//UnOp::UnOp(const UnOp & other): arg(other.arg->clone()) {}

//UnOp & UnOp::operator = (const UnOp & other){
    //delete arg;
    //arg = other.arg->clone();
    //return *this;
//}

// -----------------------------------------------------------------------------
// Value

Value::Value(const std::string & num): value(new Number(num)) {};

std::shared_ptr<Number> Value::eval() const {
    return value;
}

Value::~Value() = default;

Value * Value::clone() const {
    return new Value(*this);
}

void Value::print(std::ostream & os) const {
    os << *value;
}

// -----------------------------------------------------------------------------
// Var

Var::Var(const std::string & str): name(str) {}

Var::~Var() = default;

std::shared_ptr<Number> Var::eval() const {
    return VARIABLE_MAP.emplace(
        name, std::shared_ptr<Number>(new Number(0))
    ).first->second;
}

void Var::print(std::ostream & os) const {
    os << name;
}

Var * Var::clone() const {
    return new Var(*this);
}

// -----------------------------------------------------------------------------
// PlusBinOp

std::shared_ptr<Number> PlusBinOp::eval() const{
    return std::shared_ptr<Number>((*lhs->eval() + *rhs->eval()).clone());
}

PlusBinOp * PlusBinOp::clone() const{
    return new PlusBinOp(*this);
}

void PlusBinOp::print(std::ostream & os) const {
    os << "(+ " << *lhs << " " << *rhs << ")";
}

// -----------------------------------------------------------------------------
// MinusBinOp

std::shared_ptr<Number> MinusBinOp::eval() const{
    return std::shared_ptr<Number>((*lhs->eval() - *rhs->eval()).clone());
}

MinusBinOp * MinusBinOp::clone() const{
    return new MinusBinOp(*this);
}

void MinusBinOp::print(std::ostream & os) const {
    os << "(- " << *lhs << " " << *rhs << ")";
}

// -----------------------------------------------------------------------------
// TimesBinOp

std::shared_ptr<Number> TimesBinOp::eval() const{
    //std::cerr << "Times" << std::endl; 
    auto out = std::shared_ptr<Number>((*lhs->eval() * *rhs->eval()).clone());
    //std::cerr << "Times end" << std::endl;
    return out;
}

TimesBinOp * TimesBinOp::clone() const{
    return new TimesBinOp(*this);
}

void TimesBinOp::print(std::ostream & os) const {
    os << "(* " << *lhs << " " << *rhs << ")";
}

// -----------------------------------------------------------------------------
// DivideBinOp

std::shared_ptr<Number> DivideBinOp::eval() const{
    return std::shared_ptr<Number>((*lhs->eval() / *rhs->eval()).clone());
}

void DivideBinOp::print(std::ostream & os) const {
    os << "(/ " << *lhs << " " << *rhs << ")";
}

DivideBinOp * DivideBinOp::clone() const{
    return new DivideBinOp(*this);
}

// -----------------------------------------------------------------------------
// AsignBinOp

AsignBinOp * AsignBinOp::clone() const {
    return new AsignBinOp(*this);
}

std::shared_ptr<Number> AsignBinOp::eval() const {
    auto var = lhs->eval();
    *var = *rhs->eval();
    return var;
}

void AsignBinOp::print(std::ostream & os) const {
    os << "(= " << *lhs << " " << *rhs << ")";
}

i32 get_operator_precedense(const Token & token){
    try{
        return OP_PRECEDENSE.at(token.value);
    } catch (std::out_of_range & e) {
        return INT32_MAX;
    }
}

std::shared_ptr<ASTNode> make_bin_op(const Token & oper, std::shared_ptr<ASTNode> lhs, std::shared_ptr<ASTNode> rhs){
    if (oper.value == "+"){
        return std::shared_ptr<ASTNode>(new PlusBinOp(*lhs, *rhs));
    }
    if (oper.value == "-"){
        return std::shared_ptr<ASTNode>(new MinusBinOp(*lhs, *rhs));
    }
    if (oper.value == "*"){
        return std::shared_ptr<ASTNode>(new TimesBinOp(*lhs, *rhs));
    }
    if (oper.value == "/"){
        return std::shared_ptr<ASTNode>(new DivideBinOp(*lhs, *rhs));
    }
    if (oper.value == "="){
        return std::shared_ptr<ASTNode>(new AsignBinOp(*lhs, *rhs));
    }

    throw syntax_error("Unknown operator: " + to_string(oper));
}

std::shared_ptr<ASTNode> parse_bin_op_rhs(
    std::list<Token> & token_stream,
    std::shared_ptr<ASTNode> lhs_, i32 min_operator_precedense
){
    std::shared_ptr<ASTNode> lhs(lhs_->clone());
    while (true){
        i32 operator_precedense;
        {
            const Token & cur_tok = token_stream.front();
            // std::cout << cur_tok << " " << token_stream.size() << std::endl;
            if(cur_tok.type != TokenType::Operator)
                return lhs;
            operator_precedense = get_operator_precedense(cur_tok);
            // std::cout << operator_precedense << std::endl;
        }
        if (operator_precedense < min_operator_precedense){
            return lhs;
        }
        Token oper = token_stream.front();
        token_stream.pop_front();
        std::shared_ptr<ASTNode> rhs = parse_primary(token_stream);
        i32 next_token_precedense = get_operator_precedense(token_stream.front());
        if (operator_precedense < next_token_precedense){
            auto new_rhs = parse_bin_op_rhs(
                token_stream, rhs, operator_precedense + 1
            );
            rhs = new_rhs;
        }
        std::shared_ptr<ASTNode> new_lhs = make_bin_op(oper, lhs, rhs);
        lhs = new_lhs;
    }
}

std::shared_ptr<ASTNode> parse_paren(std::list<Token> & token_stream){
    std::shared_ptr<ASTNode> expr = parse_expr(token_stream);
    if (token_stream.front().type != TokenType::RParen)
        throw std::logic_error("Syntax error");
    token_stream.pop_front();
    return expr;
}

std::shared_ptr<ASTNode> parse_literal(std::list<Token> & token_stream){
    std::shared_ptr<ASTNode> val(new Value(token_stream.front().value));
    token_stream.pop_front();
    return val;
}

std::shared_ptr<ASTNode> parse_ident(std::list<Token> & token_stream){
    if (token_stream.front().value == "exit"){
        throw exit_exception();
    }
    if ((*std::next(token_stream.begin())).type == TokenType::LParen){
        return parse_function(token_stream);
    }
    std::shared_ptr<ASTNode> var(new Var(token_stream.front().value));
    token_stream.pop_front();
    return var;
}

std::shared_ptr<ASTNode> parse_function(std::list<Token> & token_stream){
    std::shared_ptr<Function> fun(new Function(token_stream.front().value));
    token_stream.pop_front();
    token_stream.pop_front();
    while (true){
        fun->add_expr(parse_expr(token_stream));
        if (token_stream.front().type == TokenType::RParen){
            token_stream.pop_front();
            break;
        } else if (token_stream.front().type == TokenType::Separator){
            token_stream.pop_front();
            continue;
        } else {
            std::cerr << *fun << std::endl;
            throw syntax_error(
                "Unexpected token: " + to_string(token_stream.front())
            );
        }
    }
    return fun;
}

std::shared_ptr<ASTNode> parse_primary(std::list<Token> & token_stream){
    if (token_stream.front().type == TokenType::LParen){
        token_stream.pop_front();
        return parse_paren(token_stream);
    } else if (token_stream.front().type == TokenType::Number){
        return parse_literal(token_stream);
    } else if (token_stream.front().type == TokenType::Identifier){
        std::cout << token_stream.front().value << std::endl;
        return parse_ident(token_stream);
    } else if (token_stream.front().type == TokenType::Delim){
        token_stream.pop_front();
        return parse_primary(token_stream);
    }
}

std::shared_ptr<ASTNode> parse_expr(std::list<Token> & token_stream){
    std::shared_ptr<ASTNode> lhs = parse_primary(token_stream);

    auto out = parse_bin_op_rhs(token_stream, lhs, 0);
    return out;
}

std::shared_ptr<ASTNode> parse(std::list<Token> & token_stream){
    std::shared_ptr<CodeBlock> out(new CodeBlock());
    while (token_stream.size() - 1)
        out->add_expr(parse_expr(token_stream));
    return out;
}
std::ostream & operator << (std::ostream & os, const ASTNode & ast){
    ast.print(os);
    return os;
}
