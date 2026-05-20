#include "chisq.h"


ChiSq::ChiSq(MySample *sample, Distribution d0):
_df(0),
_pval(0),
_stat(0),
_n_states(0),
_exp_freqs(nullptr),
_obs_freqs(nullptr)
{
    operator()(sample, d0);
}


void ChiSq::operator() (MySample *sample, Distribution d0){
    delete[] _exp_freqs;
    delete[] _obs_freqs;

    _stat = chisq_stat(sample->get_sample(),
               sample->get_sample_size(),
               0,
               5.0,
               d0,
               _df,
               _obs_freqs,
               _exp_freqs,
               _n_states);

    double pval = 1 - pChi(_stat, _df - 1);
    _pval = std::min(pval, 1 - 1e-6);
}

ChiSq::~ChiSq(){
    delete[] _obs_freqs;
    delete[] _exp_freqs;
}

