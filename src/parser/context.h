#pragma once

#include <unordered_map>
#include <memory>

#include "../numbers/rational.h"

struct Context {
    std::unordered_map<std::string, std::shared_ptr<Rational>> variable_map;
};