#include "numberrepresentation.h"
#include "dense.h"
#include "sparse.h"

std::shared_ptr<NumberRepresentation> find_representation(const Digits & digits){
    auto sparse = std::shared_ptr<Sparse>(new Sparse(digits));
    auto dense = std::shared_ptr<Dense>(new Dense(digits));
    if (sparse->get_size() > dense->get_size()) return dense;
    return sparse;
}