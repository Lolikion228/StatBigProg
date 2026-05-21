#include "distribution.h"

Distribution::Distribution(double lambda):
_lambda(lambda)
{}

double Distribution::get_lambda() const{
    return _lambda;
}

// внести в chisq_stat
// типа динамич массива в dist
int Distribution::get_lim(int sample_size, double cum_exp_freq_thresh) const{
    double cum_exp_freq = 0;
    double p = exp(-_lambda);
    int i=0;
    while(cum_exp_freq + sample_size * p < sample_size - cum_exp_freq_thresh){
        cum_exp_freq += sample_size * p;
        ++i;
        p *= _lambda / i;
    }
    return i+1;
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
