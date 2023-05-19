#include "tokenizer.h"

#include <regex>

std::list<Token> tokenize(std::istream & is){
    std::list<Token> out;

    std::string s;
    if (!(is >> s)){
        out.emplace_back(TokenType::Delim);
        return out;
    }
    if (s == "(")
        out.emplace_back(TokenType::LParen);
    else if (s == ")")
        out.emplace_back(TokenType::RParen);
    else if (std::regex_match(s, std::regex("[a-zA-Z]*")))
        out.emplace_back(TokenType::Identifier, s);
    else if (std::regex_match(s, std::regex("[0-9]*")))
        out.emplace_back(TokenType::Number, s);
    else if (std::regex_match(s, std::regex("[+\\-*=/%<>]*")))
        out.emplace_back(TokenType::Operator, s);
    else if (std::regex_match(s, std::regex(";*")))
        out.emplace_back(TokenType::Delim);
    else
        throw std::logic_error("Syntax error");

    out.splice(out.end(), tokenize(is));
    return out;
}

std::list<Token> tokenize(const std::string & input){
    std::stringstream ss(input);
    return tokenize(ss);
}

std::ostream & operator << (std::ostream & os, const Token & t){
    return os << "Token(" << t.type << ", " << t.value << ")";
}

std::ostream & operator << (std::ostream & os, const TokenType & t){
    switch (t)
    {
    case TokenType::Identifier:
        return os << "Identifier";
    case TokenType::LParen:
        return os << "LParen";
    case TokenType::RParen:
        return os << "RParen";
    case TokenType::Number:
        return os << "Number";
    case TokenType::Operator:
        return os << "Operator";
    case TokenType::Delim:
        return os << "Delim";
    
    default:
        return os << "Unknown(" << t << ")";
    }
}