#include "tokenizer.h"
#include <regex>

std::list<Token> tokenize(std::istream & is){
    std::list<Token> out;

    std::string s;
    if (!(is >> s))
        return out;
    if (s == "(")
        out.emplace_back(TokenType::LParen);
    else if (s == ")")
        out.emplace_back(TokenType::RParen);
    else if (std::regex_match(s, std::regex("[a-zA-Z]*")))
        out.emplace_back(TokenType::Identifier, s);
    else if (std::regex_match(s, std::regex("[0-9]*")))
        out.emplace_back(TokenType::Number, s);

    out.splice(out.end(), tokenize(is));
    return out;
}

std::ostream & operator << (std::ostream & os, const Token & t){
    return os << "Token(" << (int)t.type << ", " << t.value << ")";
}