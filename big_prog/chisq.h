#ifndef CHISQ_H
#define CHISQ_H


#include "mysample.h"
#include "funcs.h"
#include "probdist.h"

class ChiSq
{
private:
    int _n_states;
    double _pval;
    double _stat;
    int _df;
    double *_exp_freqs;
    double *_obs_freqs;
public:
    ChiSq(MySample *sample, double h0_param);
    void operator() (MySample *sample, double h0_param);
    ~ChiSq();
};

#endif // CHISQ_H
