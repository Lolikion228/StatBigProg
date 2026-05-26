#include "distribution.h"

Distribution::Distribution(double lambda):
    _lambda(lambda),
    _capacity(16),
    _n_computed(1),
    _computed_probs(new double[16]),
    _computed_cumsums(new double[16])
{
    _computed_cumsums[0] = exp(-lambda);
    _computed_probs[0]   = exp(-lambda);
}

double Distribution::get_lambda() const{
    return _lambda;
}

void Distribution::update_probs(int compute_up_to){
    if(_n_computed >= compute_up_to){return;}

    if(compute_up_to >= _capacity){
        _capacity = compute_up_to * 2;
        double *prob_tmp = new double[_capacity];
        double *cums_tmp = new double[_capacity];
        for(int i=0; i<_n_computed; ++i){
            prob_tmp[i] = _computed_probs[i];
            cums_tmp[i] = _computed_cumsums[i];
        }
        delete[] _computed_probs;
        delete[] _computed_cumsums;
        _computed_probs = prob_tmp;
        _computed_cumsums = cums_tmp;
    }

    double p = _computed_probs[_n_computed - 1];
    for(int i=_n_computed; i<compute_up_to; ++i){
        p *= _lambda / i;
        _computed_probs[i] = p;
        _computed_cumsums[i] = _computed_cumsums[i-1] + p;
    }
    _n_computed = compute_up_to;
}

void Distribution::get_probs(int right_lim, double *p){
    if(right_lim > _n_computed){
        update_probs(right_lim);
    }

    for(int i=0; i<right_lim; ++i){
        p[i] = _computed_probs[i];
    }

    p[right_lim - 1] += (1 - _computed_cumsums[right_lim - 1]);
}


const char* Distribution::whoami() const{
    return "Poisson distribution";
}


Distribution::~Distribution(){

}
