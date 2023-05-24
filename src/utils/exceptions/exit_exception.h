#pragma once

#include "text_error.h"

class exit_exception: public text_error{
public:
    exit_exception();
};