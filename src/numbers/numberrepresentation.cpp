#include "numberrepresentation.h"
#include "dense.h"

std::shared_ptr<NumberRepresentation> find_representation(const Digits & digits){
    return std::shared_ptr<Dense>(new Dense(digits));
}