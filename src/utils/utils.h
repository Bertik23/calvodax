/** @file */
#pragma once

#include <string>
#include <sstream>

/**
 * Use overloaded operator << to convert object to string.
*/
template<typename T>
std::string to_string(const T & t){
    std::ostringstream os;
    os << t;
    return os.str();
}