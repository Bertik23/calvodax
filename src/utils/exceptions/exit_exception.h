/** @file */
#pragma once

#include "text_error.h"

/**
 * Exit error exception.
 * 
 * Used when user calls exit.
*/
class exit_exception: public text_error{
public:
    exit_exception();
};