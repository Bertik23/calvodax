#include "number.h"
#include <vector>

class Integer : public Number {
private:
    std::vector<unsigned long long> numbers;
    bool is_negative = false;
};
