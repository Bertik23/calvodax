#pragma once

#include <string>
#include <exception>

class text_error: public std::exception{
public:
    text_error(const std::string &);
    const char * what() const noexcept override;
private:
    std::string message;
};