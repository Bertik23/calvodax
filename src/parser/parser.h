/** @file */
#pragma once

#include <list>
#include <memory>

#include "../typedefs.h"
#include "tokenizer.h"
#include "../ast/astnode.h"

/**
 * Parses token stream
 * 
 * @param `token_stream` mutable token stream
 *  destructively parses this stream.
 *  Expects stream to be Token(Delim) terminated
 * @throw `syntax_error` on invalid syntax
*/
std::shared_ptr<ASTNode> parse(std::list<Token> & token_stream);
/**
 * Parses expresion from token stream
 * 
 * @param `token_stream` mutable token stream
 *  destructively parses this stream.
 *  Expects stream to be Token(Delim) terminated
 * @throw `syntax_error` on invalid syntax
*/
std::shared_ptr<ASTNode> parse_expr(std::list<Token> &);
/**
 * Parses parenthesis from token stream
 * 
 * @param `token_stream` mutable token stream
 *  destructively parses this stream.
 *  Expects stream to be Token(Delim) terminated
 * @throw `syntax_error` on invalid syntax
*/
std::shared_ptr<ASTNode> parse_paren(std::list<Token> &);
/**
 * Parses primary expresion from token stream
 * 
 * @param `token_stream` mutable token stream
 *  destructively parses this stream.
 *  Expects stream to be Token(Delim) terminated
 * @throw `syntax_error` on invalid syntax
*/
std::shared_ptr<ASTNode> parse_primary(std::list<Token> &);
/**
 * Parses identifier from token stream
 * 
 * @param `token_stream` mutable token stream
 *  destructively parses this stream.
 *  Expects stream to be Token(Delim) terminated
 * @throw `syntax_error` on invalid syntax
*/
std::shared_ptr<ASTNode> parse_ident(std::list<Token> &);
/**
 * Parses export command from token stream
 * 
 * @param `token_stream` mutable token stream
 *  destructively parses this stream.
 *  Expects stream to be Token(Delim) terminated
 * @throw `syntax_error` on invalid syntax
*/
std::shared_ptr<ASTNode> parse_export(std::list<Token> &);
/**
 * Parses import command from token stream
 * 
 * @param `token_stream` mutable token stream
 *  destructively parses this stream.
 *  Expects stream to be Token(Delim) terminated
 * @throw `syntax_error` on invalid syntax
*/
std::shared_ptr<ASTNode> parse_import(std::list<Token> &);
/**
 * Parses function call from token stream
 * 
 * @param token_stream mutable token stream
 *  destructively parses this stream.
 *  Expects stream to be Token(Delim) terminated
 * @throw `syntax_error` on invalid syntax
*/
std::shared_ptr<ASTNode> parse_function(std::list<Token> &);
/**
 * Parses rhs of binary operator token stream
 * 
 * @param `token_stream` mutable token stream
 *  destructively parses this stream.
 *  Expects stream to be Token(Delim) terminated
 * 
 * @param `lhs` pointer to lhs of binary operator
 * 
 * @param `min_operator_precedense` minimal operator precedense to parse
 * 
 * @throw `syntax_error` on invalid syntax
*/
std::shared_ptr<ASTNode> parse_bin_op_rhs(
    std::list<Token> & token_stream,
    ASTNode * lhs,
    i32 min_operator_precedense
);
