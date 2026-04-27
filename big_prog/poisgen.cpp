#include "poisgen.h"

PoisGen::PoisGen(double lambda, std::mt19937_64* stdgen):
    _stdgen(stdgen),
    _lambda(lambda)
{

}

PoisGen::~PoisGen(){

}
