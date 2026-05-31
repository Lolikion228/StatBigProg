#include "poisgen2.h"

int PoisGenKnuth::gen(){
    double t = 1;
    double c = exp(-_lambda);
    int n = 0;

    t *= _stdgen->operator()() / (double)std::numeric_limits<uint64_t>::max();

    while (t >= c){
        t *= _stdgen->operator()() / (double)std::numeric_limits<uint64_t>::max();
        ++n;
    }

    return n;
}
