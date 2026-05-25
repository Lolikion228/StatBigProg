#include "poisgen.h"

PoisGen::PoisGen(Distribution *dist, std::mt19937_64* stdgen):
    _dist(dist),
    _stdgen(stdgen),
    _lambda(dist->get_lambda())
{

}

PoisGen::~PoisGen(){

}
