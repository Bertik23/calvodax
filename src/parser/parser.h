#pragma once

#include <list>
#include <memory>

#include "../typedefs.h"
#include "tokenizer.h"
#include "../ast/astnode.h"

std::shared_ptr<ASTNode> parse(std::list<Token> &);
std::shared_ptr<ASTNode> parse_expr(std::list<Token> &);
std::shared_ptr<ASTNode> parse_paren(std::list<Token> &);
std::shared_ptr<ASTNode> parse_primary(std::list<Token> &);
std::shared_ptr<ASTNode> parse_ident(std::list<Token> &);
std::shared_ptr<ASTNode> parse_export(std::list<Token> &);
std::shared_ptr<ASTNode> parse_import(std::list<Token> &);
std::shared_ptr<ASTNode> parse_function(std::list<Token> &);
std::shared_ptr<ASTNode> parse_bin_op_rhs(std::list<Token> &, ASTNode *, i32);
