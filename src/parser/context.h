/** @file */
#pragma once

#include <unordered_map>
#include <memory>

#include "../numbers/rational.h"

/**
 * Struct for holding context of current evalueation.
*/
struct Context {
    Context();
    std::unordered_map<std::string, std::shared_ptr<Rational>> variable_map;
};