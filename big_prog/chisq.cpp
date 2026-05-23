#include "chisq.h"


ChiSq::ChiSq(MySample *sample, Distribution *d0):
_dist(d0),
_df(0),
_pval(0),
_stat(0),
_n_states(0),
_exp_freqs(nullptr),
_obs_freqs(nullptr)
{
    set_sample(sample, d0);
}


void ChiSq::set_sample(MySample *sample, Distribution* d0){
    _dist = d0;
    _n_states = this->get_lim(sample->get_sample_size());
    double* p = new double[_n_states]{};
    _dist->get_probs(_n_states, p);

    delete[] _exp_freqs;
    delete[] _obs_freqs;
    _obs_freqs = new double[_n_states]{};
    _exp_freqs = new double[_n_states]{};
    this->compute_freqs(p, sample);

    _stat = this->compute_chisq_stat();

    double pval = 1 - pChi(_stat, _df);
    _pval = std::min(pval, 1 - 1e-6);

    delete[] p;
}


int ChiSq::get_lim(int sample_size) const{
    double lambda = _dist->get_lambda();
    double cum_exp_freq = 0;
    double p = exp(-lambda);
    int i=0;
    while(cum_exp_freq + sample_size * p < sample_size - CUM_EXP_FREQ_THRESH){
        cum_exp_freq += sample_size * p;
        ++i;
        p *= lambda / i;
    }
    return i+1;
}


void ChiSq::compute_freqs(double *p, MySample *sample){
    int sample_size = sample->get_sample_size();
    int *X = sample->get_sample();

    for(int i=0; i<sample_size; ++i){
        if( X[i] >= (_n_states - 1) ) {
            ++_obs_freqs[_n_states - 1];
        }
        else {
            ++_obs_freqs[ X[i] ];
        }
    }

    for(int i=0; i<_n_states; ++i){
        _exp_freqs[i] = sample_size * p[i];
    }
}


double ChiSq::compute_chisq_stat(){
    double res = 0;
    double cum_exp_freq = 0;
    double cum_obs_freq = 0;
    int cnt_groups = 0;
    double diff;
    double summand;

    for(int i=0; i<_n_states; ++i){
        cum_obs_freq += _obs_freqs[i];
        cum_exp_freq += _exp_freqs[i];
        if(cum_exp_freq >= CUM_EXP_FREQ_THRESH){
            diff = cum_obs_freq - cum_exp_freq;
            summand = diff * diff / cum_exp_freq;
            res += summand;
            cum_exp_freq = 0;
            cum_obs_freq = 0;
            ++cnt_groups;
        }
    }

    if(cum_exp_freq != 0){
        diff = cum_obs_freq - cum_exp_freq;
        summand = diff * diff / cum_exp_freq;
        res += summand;
        ++cnt_groups;
    }

    _df = cnt_groups - 1;

    return res;
}


ChiSq::~ChiSq(){
    delete[] _obs_freqs;
    delete[] _exp_freqs;
}

