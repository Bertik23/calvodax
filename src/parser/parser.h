#pragma once

#include <unordered_map>
#include <string>
#include <list>
#include <memory>

#include "../typedefs.h"
#include "../numbers/integer.h"
#include "../numbers/rational.h"
#include "tokenizer.h"

extern std::unordered_map<std::string, i32> OP_PRECEDENSE;

class ASTNode{
public:
    virtual ~ASTNode() = default;
    virtual std::shared_ptr<Rational> eval() const = 0;
    virtual ASTNode * clone() const = 0;
    virtual void print(std::ostream &) const = 0;
};

class Export: public ASTNode{
public:
    Export(const std::string &);
    ~Export() override;
    std::shared_ptr<Rational> eval() const override;
    Export * clone() const override;
    void print(std::ostream &) const override;
private:
    std::string file;
};

class Import: public ASTNode{
public:
    Import(const std::string &);
    ~Import() override;
    std::shared_ptr<Rational> eval() const override;
    Import * clone() const override;
    void print(std::ostream &) const override;
private:
    std::string file;
};

class CodeBlock : public ASTNode {
public:
    CodeBlock();
    ~CodeBlock() override = default;
    std::shared_ptr<Rational> eval() const override;
    CodeBlock * clone() const override;
    void print(std::ostream &) const override;   
    void add_expr(std::shared_ptr<ASTNode>);
protected:
    std::vector<std::shared_ptr<ASTNode>> expresions;
};

class Function : public CodeBlock {
public:
    Function(const std::string &);
    std::shared_ptr<Rational> eval() const override;
    Function * clone() const override;
    void print(std::ostream &) const override;
protected:
    std::string name;
};

class BinOp : public ASTNode{
public:
    BinOp(const ASTNode & lhs, const ASTNode & rhs);
    // BinOp(const BinOp &);
    // BinOp & operator = (const BinOp &);
    // ~BinOp() override;
protected:
    std::shared_ptr<ASTNode> lhs;
    std::shared_ptr<ASTNode> rhs;
};

class UnOp : public ASTNode{
public:
    UnOp(const ASTNode & arg);
    // ~UnOp() override;
    // UnOp(const UnOp &);
    // UnOp & operator = (const UnOp &);
protected:
    std::shared_ptr<ASTNode> arg;
};

class Value : public ASTNode{
public:
    Value(const std::string &);
    ~Value() override;
    std::shared_ptr<Rational> eval() const override;
    Value * clone() const override;
    void print(std::ostream &) const override;
protected:
    std::shared_ptr<Rational> value;
};

class Var : public ASTNode{
public:
    Var(const std::string &);
    ~Var() override;
    std::shared_ptr<Rational> eval() const override;
    Var * clone() const override;
    void print(std::ostream &) const override;
private:
    std::string name;
};

class PlusBinOp: public BinOp{
public:
    using BinOp::BinOp;
    std::shared_ptr<Rational> eval() const override;
    PlusBinOp * clone() const override;
    void print(std::ostream &) const override;
};

class MinusBinOp: public BinOp{
public:
    using BinOp::BinOp;
    std::shared_ptr<Rational> eval() const override;
    MinusBinOp * clone() const override;
    void print(std::ostream &) const override;
};

class TimesBinOp: public BinOp{
public:
    using BinOp::BinOp;
    std::shared_ptr<Rational> eval() const override;
    TimesBinOp * clone() const override;
    void print(std::ostream &) const override;
};

class DivideBinOp: public BinOp{
public:
    using BinOp::BinOp;
    std::shared_ptr<Rational> eval() const override;
    DivideBinOp * clone() const override;
    void print(std::ostream &) const override;
};

class PowerBinOp: public BinOp{
public:
    using BinOp::BinOp;
    std::shared_ptr<Rational> eval() const override;
    PowerBinOp * clone() const override;
    void print(std::ostream &) const override;
};

class AsignBinOp: public BinOp{
public:
    using BinOp::BinOp;
    std::shared_ptr<Rational> eval() const override;
    AsignBinOp * clone() const override;
    void print(std::ostream &) const override;
};

std::shared_ptr<ASTNode> parse(std::list<Token> &);
std::shared_ptr<ASTNode> parse_expr(std::list<Token> &);
std::shared_ptr<ASTNode> parse_paren(std::list<Token> &);
std::shared_ptr<ASTNode> parse_primary(std::list<Token> &);
std::shared_ptr<ASTNode> parse_ident(std::list<Token> &);
std::shared_ptr<ASTNode> parse_export(std::list<Token> &);
std::shared_ptr<ASTNode> parse_import(std::list<Token> &);
std::shared_ptr<ASTNode> parse_function(std::list<Token> &);
std::shared_ptr<ASTNode> parse_bin_op_rhs(std::list<Token> &, ASTNode *, i32);

std::ostream & operator << (std::ostream &, const ASTNode &);