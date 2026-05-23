#include "distribution.h"

Distribution::Distribution(double lambda):
_lambda(lambda)
{}

double Distribution::get_lambda() const{
    return _lambda;
}

void Distribution::get_probs(int right_lim, double *p) const{
    double t = exp(-_lambda);
    double sum = t;
    p[0] = t;
    for(int i=1; i<right_lim; ++i){
        t *= _lambda / i;
        p[i] = t;
        sum += p[i];
    }
    p[right_lim - 1] += (1 - sum);
}


const char* Distribution::whoami() const{
    return "Poisson distribution";
};


Distribution::~Distribution(){

}
