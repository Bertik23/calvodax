#include "exceptions.h"

text_error::text_error(const std::string & msg): message(msg) {}

const char * text_error::what() const noexcept{
    return message.c_str();
}

exit_exception::exit_exception(): text_error("Exit"){}
