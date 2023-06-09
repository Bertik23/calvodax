#include "tokenizer.h"

#include <regex>

#include "../utils/exceptions.h"
#include "../typedefs.h"

Token::Token(TokenType type, std::string value): type(type), value(value) {}

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
    else if (std::regex_match(s, std::regex("[-+]?[0-9]+")))
        out.emplace_back(TokenType::Number, s);
    else if (std::regex_match(s, std::regex("[-+]?0x[0-9A-Fa-f]+")))
        out.emplace_back(TokenType::Number, s);
    else if (std::regex_match(s, std::regex("[-+*=/%<>^]*")))
        out.emplace_back(TokenType::Operator, s);
    else if (std::regex_match(s, std::regex(";*")))
        out.emplace_back(TokenType::Delim);
    else if (s == ",")
        out.emplace_back(TokenType::Separator);
    else if (std::regex_match(s, std::regex("[a-zA-Z]+")))
        out.emplace_back(TokenType::Identifier, s);
    else if (std::regex_match(s, std::regex(R"([a-zA-Z0-9\./]+)")))
        out.emplace_back(TokenType::FileName, s);
    else
        throw syntax_error("Unrecognised token: " + s);

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
    case TokenType::FileName:
        return os << "FileName";
    
    default:
        return os << "Unknown(" << (u32) t << ")";
    }
}