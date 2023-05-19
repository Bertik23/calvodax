#include "parser.h"

#include <unordered_map>
#include <sstream>

#include "../utils/defaut_ptr.h"

static std::unordered_map<std::string, default_ptr<Number>> VARIABLE_MAP;

// -----------------------------------------------------------------------------
// CodeBlock

Number * CodeBlock::eval() const {
    if (expresions.size() == 0) return new Number();

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

void CodeBlock::add_expr(ASTNode * ast){
    expresions.emplace_back(ast);
}

// -----------------------------------------------------------------------------
// BinOp

BinOp::BinOp(const ASTNode & lhs, const ASTNode & rhs)
     : lhs(lhs.clone()), rhs(rhs.clone()){}

BinOp::~BinOp(){
    delete lhs;
    delete rhs;
}

BinOp::BinOp(const BinOp & other): lhs(other.lhs->clone()), rhs(other.rhs->clone()) {}

BinOp & BinOp::operator = (const BinOp & other){
    delete lhs;
    delete rhs;
    lhs = other.lhs->clone();
    rhs = other.rhs->clone();
    return *this;
}

// -----------------------------------------------------------------------------
// UnOp

UnOp::UnOp(const ASTNode & arg): arg(arg.clone()){}

UnOp::~UnOp(){
    delete arg;
}

UnOp::UnOp(const UnOp & other): arg(other.arg->clone()) {}

UnOp & UnOp::operator = (const UnOp & other){
    delete arg;
    arg = other.arg->clone();
    return *this;
}

// -----------------------------------------------------------------------------
// Value

Value::Value(const std::string & num): value(new Number(num)) {};

Number * Value::eval() const {
    return &*value;
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

Number * Var::eval() const {
    return &*VARIABLE_MAP[name];
}

void Var::print(std::ostream & os) const {
    os << name;
}

Var * Var::clone() const {
    return new Var(*this);
}

// -----------------------------------------------------------------------------
// PlusBinOp

Number * PlusBinOp::eval() const{
    return (*lhs->eval() + *rhs->eval()).clone();
}

PlusBinOp * PlusBinOp::clone() const{
    return new PlusBinOp(*this);
}

void PlusBinOp::print(std::ostream & os) const {
    os << "(+ " << *lhs << " " << *rhs << ")";
}

// -----------------------------------------------------------------------------
// MinusBinOp

Number * MinusBinOp::eval() const{
    return (*lhs->eval() - *rhs->eval()).clone();
}

MinusBinOp * MinusBinOp::clone() const{
    return new MinusBinOp(*this);
}

void MinusBinOp::print(std::ostream & os) const {
    os << "(- " << *lhs << " " << *rhs << ")";
}

// -----------------------------------------------------------------------------
// TimesBinOp

Number * TimesBinOp::eval() const{
    return (*lhs->eval() * *rhs->eval()).clone();
}

TimesBinOp * TimesBinOp::clone() const{
    return new TimesBinOp(*this);
}

void TimesBinOp::print(std::ostream & os) const {
    os << "(* " << *lhs << " " << *rhs << ")";
}

// -----------------------------------------------------------------------------
// DivideBinOp

Number * DivideBinOp::eval() const{
    return (*lhs->eval() / *rhs->eval()).clone();
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

Number * AsignBinOp::eval() const {
    return &(*(lhs->eval()) = *rhs->eval());
}

void AsignBinOp::print(std::ostream & os) const {
    os << "(= " << *lhs << " " << *rhs << ")";
}

i32 get_operator_precedense(const Token & token){
    try{
        return OP_PRECEDENSE.at(token.value);
    } catch (std::out_of_range & e) {
        return INT32_MIN;
    }
}

ASTNode * make_bin_op(const Token & oper, ASTNode * lhs, ASTNode * rhs){
    if (oper.value == "+"){
        return new PlusBinOp(*lhs, *rhs);
    }
    if (oper.value == "-"){
        return new MinusBinOp(*lhs, *rhs);
    }
    if (oper.value == "*"){
        return new TimesBinOp(*lhs, *rhs);
    }
    if (oper.value == "/"){
        return new DivideBinOp(*lhs, *rhs);
    }
    if (oper.value == "="){
        return new AsignBinOp(*lhs, *rhs);
    }
    std::ostringstream os("1 2");
    os << oper;
    throw std::logic_error(std::string("Not wtf") + os.str() );
}

ASTNode * parse_bin_op_rhs(std::list<Token> & token_stream, ASTNode * lhs_, i32 min_operator_precedense){
    ASTNode * lhs = lhs_->clone();
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
        ASTNode * rhs = parse_primary(token_stream);
        i32 next_token_precedense = get_operator_precedense(token_stream.front());
        if (operator_precedense < next_token_precedense){
            rhs = parse_bin_op_rhs(token_stream, rhs, operator_precedense + 1);
        }
        lhs = make_bin_op(oper, lhs, rhs);
    }
}

ASTNode * parse_paren(std::list<Token> & token_stream){
    ASTNode * expr = parse_expr(token_stream);
    if (token_stream.front().type != TokenType::RParen)
        throw std::logic_error("Syntax error");
    token_stream.pop_front();
    return expr;
}

ASTNode * parse_literal(std::list<Token> & token_stream){
    Value * val = new Value(token_stream.front().value);
    token_stream.pop_front();
    return val;
}

ASTNode * parse_ident(std::list<Token> & token_stream){
    Var * var = new Var(token_stream.front().value);
    token_stream.pop_front();
    return var;
}

ASTNode * parse_primary(std::list<Token> & token_stream){
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

ASTNode * parse_expr(std::list<Token> & token_stream){
    ASTNode * lhs = parse_primary(token_stream);

    return parse_bin_op_rhs(token_stream, lhs, 0);
}

ASTNode * parse(std::list<Token> & token_stream){
    CodeBlock * out = new CodeBlock();
    while (token_stream.size() - 1)
        out->add_expr(parse_expr(token_stream)->clone());
    return out;
}
std::ostream & operator << (std::ostream & os, const ASTNode & ast){
    ast.print(os);
    return os;
}
