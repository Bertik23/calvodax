/** @file */ 

#pragma once

#include <string>
#include <list>
#include <iostream>

/**
 * Token type enum.
 * 
 * Stores all types of tokens.
*/
enum class TokenType{
    Identifier,
    LParen,
    RParen,
    Number,
    Operator,
    Delim,
    Separator,
    FileName
};

std::ostream & operator << (std::ostream & os, const TokenType & t);

/**
 * Struct for holding a token.
 * 
 * Holds type and value.
*/
struct Token{
    /**
     * @param `TokenType` type of the token.
     * @param `std::string` value of the token. Defaults to "".
    */
    Token(TokenType type, std::string value = "");
    const TokenType type;
    const std::string value;
};

/**
 * Tokenizes input stream.
 * 
 * @return `std::list<Token>` stream of tokens 
*/
std::list<Token> tokenize(std::istream &);
/**
 * Tokenizes string.
 * 
 * @return `std::list<Token>` stream of tokens
*/
std::list<Token> tokenize(const std::string &);


std::ostream & operator << (std::ostream & os, const Token & t);