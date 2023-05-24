#pragma once

#include "text_error.h"

class syntax_error: public text_error{
    using text_error::text_error;
};