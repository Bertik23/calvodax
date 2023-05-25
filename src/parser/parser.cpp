#include "parser.h"

#include <unordered_map>
#include <sstream>
#include <functional>
#include <filesystem>
#include <fstream>

#include "../utils/exceptions.h"
#include "../utils/utils.h"
#include "context.h"

#include "../ast/asignbinop.h"
#include "../ast/astnode.h"
#include "../ast/binop.h"
#include "../ast/codeblock.h"
#include "../ast/dividebinop.h"
#include "../ast/export.h"
#include "../ast/function.h"
#include "../ast/import.h"
#include "../ast/minusbinop.h"
#include "../ast/modulobinop.h"
#include "../ast/plusbinop.h"
#include "../ast/powerbinop.h"
#include "../ast/timesbinop.h"
#include "../ast/unop.h"
#include "../ast/value.h"
#include "../ast/var.h"

const std::unordered_map<std::string, i32> OP_PRECEDENSE {
    {"=", 1},
    {"+", 10},
    {"-", 10},
    {"*", 20},
    {"/", 20},
    {"^", 30},
    {"<", 5},
    {">", 5},
};

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
    if (oper.value == "^"){
        return std::shared_ptr<ASTNode>(new PowerBinOp(*lhs, *rhs));
    }
    if (oper.value == "%"){
        return std::shared_ptr<ASTNode>(new ModuloBinOp(*lhs, *rhs));
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
            if(cur_tok.type != TokenType::Operator)
                return lhs;
            operator_precedense = get_operator_precedense(cur_tok);
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
        throw text_error("Syntax error");
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
    if (token_stream.front().value == "export"){
        token_stream.pop_front();
        return parse_export(token_stream);
    }
    if (token_stream.front().value == "import"){
        token_stream.pop_front();
        return parse_import(token_stream);
    }
    if ((*std::next(token_stream.begin())).type == TokenType::LParen){
        return parse_function(token_stream);
    }
    std::shared_ptr<ASTNode> var(new Var(token_stream.front().value));
    token_stream.pop_front();
    return var;
}

std::shared_ptr<ASTNode> parse_export(std::list<Token> & token_stream){
    if (token_stream.front().type != TokenType::FileName)
        throw syntax_error("Unexpected token: " + to_string(token_stream.front()));
    auto out = std::shared_ptr<Export>(new Export(token_stream.front().value));
    token_stream.pop_front();
    return out;
}

std::shared_ptr<ASTNode> parse_import(std::list<Token> & token_stream){
    if (token_stream.front().type != TokenType::FileName)
        throw syntax_error("Unexpected token: " + to_string(token_stream.front()));
    auto out = std::shared_ptr<Import>(new Import(token_stream.front().value));
    token_stream.pop_front();
    return out;
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
        return parse_ident(token_stream);
    } else if (token_stream.front().type == TokenType::Delim){
        throw syntax_error("Unexpected delimeter.");
        token_stream.pop_front();
        return parse_primary(token_stream);
    }
    throw syntax_error("Unexpected token: " + to_string(token_stream.front()));
}

std::shared_ptr<ASTNode> parse_expr(std::list<Token> & token_stream){
    std::shared_ptr<ASTNode> lhs = parse_primary(token_stream);

    auto out = parse_bin_op_rhs(token_stream, lhs, 0);
    return out;
}

std::shared_ptr<ASTNode> parse(std::list<Token> & token_stream){
    std::shared_ptr<CodeBlock> out(new CodeBlock());
    while (token_stream.size() > 0){
        out->add_expr(parse_expr(token_stream));
        if (token_stream.front().type != TokenType::Delim)
            throw syntax_error(
                "Unexpected token: " + to_string(token_stream.front())
            );
        token_stream.pop_front();
    }
    return out;
}