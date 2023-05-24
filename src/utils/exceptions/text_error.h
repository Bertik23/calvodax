/** @file */
#pragma once

#include <string>
#include <exception>

/**
 * Base text error exception.
*/
class text_error: public std::exception{
public:
    /**
     * Constructs exception with message.
     * 
     * @param `std::string` message of the exception
    */
    text_error(const std::string &);
    /**
     * Returns an explanatory string.
    */
    const char * what() const noexcept override;
private:
    std::string message;
};