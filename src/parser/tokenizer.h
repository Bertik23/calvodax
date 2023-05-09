#include <string>
#include <list>
#include <iostream>

enum class TokenType{
    Identifier,
    LParen,
    RParen,
    Number
};

struct Token{
    Token(TokenType type, std::string value = ""): type(type), value(value) {};
    const TokenType type;
    const std::string value;
};

std::list<Token> tokenize(std::istream &);

std::ostream & operator << (std::ostream & os, const Token & t);