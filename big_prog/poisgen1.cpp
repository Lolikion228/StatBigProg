#include "poisgen1.h"


int PoisGen1::gen(){
    double p = exp(-_lambda);
    double s = p;
    int k = 0;

    double alpha = _stdgen->operator()() / (double)std::numeric_limits<uint64_t>::max();

    while(alpha > s){
        ++k;
        p *= _lambda / k;
        s += p;
    }

    return k;
}
