#include "numberrepresentation.h"
#include "dense.h"
#include "sparse.h"

std::shared_ptr<NumberRepresentation> find_representation(const Digits & digits){
    auto bits = digits.as_bits();
    usize bs = 0;
    for (const auto & b: bits){
        bs += b;
    }
    return std::shared_ptr<Sparse>(new Sparse(digits));
    return std::shared_ptr<Dense>(new Dense(digits));
}