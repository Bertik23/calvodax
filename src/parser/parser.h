#pragma once

#include <unordered_map>
#include <string>
#include <list>

#include "../typedefs.h"
#include "../numbers/number.h"
#include "tokenizer.h"
#include "../utils/defaut_ptr.h"

static std::unordered_map<std::string, i32> OP_PRECEDENSE {
    {"=", 1},
    {"+", 10},
    {"-", 10},
    {"*", 20},
    {"/", 20}
};

class ASTNode{
public:
    virtual ~ASTNode() = default;
    virtual Number * eval() const = 0;
    virtual ASTNode * clone() const = 0;
    virtual void print(std::ostream &) const = 0;
};

class CodeBlock : public ASTNode {
public:
    CodeBlock() = default;
    ~CodeBlock() override = default;
    Number * eval() const override;
    CodeBlock * clone() const override;
    void print(std::ostream &) const override;   
    void add_expr(ASTNode *);
protected:
    std::vector<default_ptr<ASTNode>> expresions;
};

class BinOp : public ASTNode{
public:
    BinOp(const ASTNode & lhs, const ASTNode & rhs);
    BinOp(const BinOp &);
    BinOp & operator = (const BinOp &);
    ~BinOp() override;
protected:
    ASTNode * lhs;
    ASTNode * rhs;
};

class UnOp : public ASTNode{
public:
    UnOp(const ASTNode & arg);
    ~UnOp() override;
protected:
    ASTNode * arg;
};

class Value : public ASTNode{
public:
    Value(const std::string &);
    ~Value() override;
    Number * eval() const override;
    Value * clone() const override;
    void print(std::ostream &) const override;
protected:
    default_ptr<Number> value;
};

class Var : public ASTNode{
public:
    Var(const std::string &);
    ~Var() override;
    Number * eval() const override;
    Var * clone() const override;
    void print(std::ostream &) const override;
private:
    std::string name;
};

class PlusBinOp: public BinOp{
public:
    using BinOp::BinOp;
    Number * eval() const override;
    PlusBinOp * clone() const override;
    void print(std::ostream &) const override;
};

class MinusBinOp: public BinOp{
public:
    using BinOp::BinOp;
    Number * eval() const override;
    MinusBinOp * clone() const override;
    void print(std::ostream &) const override;
};

class TimesBinOp: public BinOp{
public:
    using BinOp::BinOp;
    Number * eval() const override;
    TimesBinOp * clone() const override;
    void print(std::ostream &) const override;
};

class DivideBinOp: public BinOp{
public:
    using BinOp::BinOp;
    Number * eval() const override;
    DivideBinOp * clone() const override;
    void print(std::ostream &) const override;
};

class AsignBinOp: public BinOp{
public:
    using BinOp::BinOp;
    Number * eval() const override;
    AsignBinOp * clone() const override;
    void print(std::ostream &) const override;
};

ASTNode * parse(std::list<Token> &);
ASTNode * parse_expr(std::list<Token> &);
ASTNode * parse_paren(std::list<Token> &);
ASTNode * parse_primary(std::list<Token> &);
ASTNode * parse_ident(std::list<Token> &);
ASTNode * parse_bin_op_rhs(std::list<Token> &, ASTNode *, i32);

std::ostream & operator << (std::ostream &, const ASTNode &);