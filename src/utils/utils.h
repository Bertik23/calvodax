#pragma once

#include <string>
#include <sstream>

template<typename T>
std::string to_string(const T & t){
    std::ostringstream os;
    os << t;
    return os.str();
}