#ifndef CHISQ_H
#define CHISQ_H


#include "mysample.h"
#include "funcs.h"
#include "probdist.h"

class ChiSq
{
private:

public:
    double _pval;
    double _stat;
    int _df;
    int _n_states;
    double *_exp_freqs;
    double *_obs_freqs;

    ChiSq(MySample *sample, Distribution d0);
    void set_sample(MySample *sample, Distribution d0);
    ~ChiSq();
};

#endif // CHISQ_H
