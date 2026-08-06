#include "chisq.h"
//#include <QDebug>

ChiSq::ChiSq(PoisGen *gen, Distribution *d0):
_df(0),
_pval(0),
_stat(0),
_n_states(0),
_exp_freqs(nullptr),
_obs_freqs(nullptr)
{
    set_sample(gen, d0);
}


void ChiSq::set_sample(PoisGen *gen, Distribution* d0){
    _n_states = this->get_lim(gen->_sample_size, d0);
    double* p = new double[_n_states]{};
    d0->get_probs(_n_states, p);

    delete[] _exp_freqs;
    delete[] _obs_freqs;
    _obs_freqs = new double[_n_states]{};
    _exp_freqs = new double[_n_states]{};
    this->compute_freqs(p, gen);

    _stat = this->compute_chisq_stat();

    double pval = 1 - pChi(_stat, _df);
    _pval = std::min(pval, 1 - 1e-6);


    delete[] p;
}

int ChiSq::get_lim(int sample_size, Distribution* dist){
    int i=0;
    while(sample_size * dist->_computed_cumsums[i] < sample_size - CUM_EXP_FREQ_THRESH){
        ++i;
        if(i>=dist->_n_computed){
            dist->update_probs(2 * i + 2);
        }
    }
    return i+1;
}


void ChiSq::compute_freqs(double *p, PoisGen *gen){
    int sample_size = gen -> _sample_size;
    int *X = gen -> _sample;

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



ChiSq::ChiSq(const ChiSq& other) :
    _pval(other._pval),
    _stat(other._stat),
    _df(other._df),
    _n_states(other._n_states),
    _exp_freqs(nullptr),
    _obs_freqs(nullptr)
{
    if (other._exp_freqs && _n_states > 0) {
        _exp_freqs = new double[_n_states];
        _obs_freqs = new double[_n_states];
        for (int i = 0; i < _n_states; ++i) {
            _exp_freqs[i] = other._exp_freqs[i];
            _obs_freqs[i] = other._obs_freqs[i];
        }
    }
}


ChiSq::ChiSq(ChiSq&& other) :
    _pval(other._pval),
    _stat(other._stat),
    _df(other._df),
    _n_states(other._n_states),
    _exp_freqs(other._exp_freqs),
    _obs_freqs(other._obs_freqs)
{
    other._exp_freqs = nullptr;
    other._obs_freqs = nullptr;
    other._n_states = 0;
}


ChiSq& ChiSq::operator=(const ChiSq& other) {
    if (this == &other) {
        return *this;
    }

    delete[] _exp_freqs;
    delete[] _obs_freqs;

    _pval = other._pval;
    _stat = other._stat;
    _df = other._df;
    _n_states = other._n_states;

    if (other._exp_freqs && _n_states > 0) {
        _exp_freqs = new double[_n_states];
        _obs_freqs = new double[_n_states];
        for (int i = 0; i < _n_states; ++i) {
            _exp_freqs[i] = other._exp_freqs[i];
            _obs_freqs[i] = other._obs_freqs[i];
        }
    } else {
        _exp_freqs = nullptr;
        _obs_freqs = nullptr;
    }

    return *this;
}

ChiSq& ChiSq::operator=(ChiSq&& other) {
    if (this == &other) {
        return *this;
    }

    delete[] _exp_freqs;
    delete[] _obs_freqs;

    _pval = other._pval;
    _stat = other._stat;
    _df = other._df;
    _n_states = other._n_states;
    _exp_freqs = other._exp_freqs;
    _obs_freqs = other._obs_freqs;

    other._exp_freqs = nullptr;
    other._obs_freqs = nullptr;
    other._n_states = 0;

    return *this;
}


ChiSq::~ChiSq(){
    delete[] _obs_freqs;
    delete[] _exp_freqs;
}

