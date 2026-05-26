#ifndef CHISQ_H
#define CHISQ_H


#include "mysample.h"
#include "funcs.h"
#include "probdist.h"
#include "poisgen.h"

const double CUM_EXP_FREQ_THRESH = 5.0;

class ChiSq
{
private:
    double compute_chisq_stat();
    int get_lim(int sample_size);
    void compute_freqs(double *p, PoisGen *gen);
public:
    Distribution *_dist;
    double _pval;
    double _stat;
    int _df;
    int _n_states;
    double *_exp_freqs;
    double *_obs_freqs;

    ChiSq(PoisGen *gen, Distribution *d0);
    void set_sample(PoisGen *gen, Distribution *d0);

    ~ChiSq();
};

#endif // CHISQ_H
