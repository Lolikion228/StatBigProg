#include "mod.h"
#include "QDebug"
const double GOOD_STEP_SIZE = 0.05;
const double GOOD_CUM_EXP_FREQ_THRESH = 5.0;
const double EPS = 1e-6;
const double ALMOST_ONE = 1.0 - EPS;


double pval(Distribution *d0, PoisGen* h1_gen, int sample_size){
    h1_gen->gen_sample(sample_size);
    ChiSq test(h1_gen, d0);

    double res1 = 1 - pChi(test._stat, test._df);

    return std::min(res1, ALMOST_ONE);
}

void psample(Distribution *d0, PoisGen* h1_gen, int psample_size,
             double *X, int main_sample_size){
    for(int i=0; i<psample_size; ++i)
        X[i] = pval(d0, h1_gen, main_sample_size);
}


//F must be F[ (int) (1 / step_size) ]
// X[i] must be from [0,1)  [1 excluded]
void ecdf(double *X, int N, double step_size, double *F){
    int n_bins = (1.0 / step_size);
    for(int i=0; i<N; ++i) ++F[ (int) (X[i] * n_bins) ]; // if X[i]=1 then =(

    F[0] = F[0] / N;
    for(int i=1; i<n_bins; ++i){
        F[i] = F[i-1] + F[i] / N;
    }

}

void pecdf(PoisGen* h0_gen, PoisGen* h1_gen, double alpha,
           int psample_size, int main_sample_size){

    int N = 1 / GOOD_STEP_SIZE;
    Distribution* d0 = new Distribution(h0_gen->_lambda);

    double* p0 = new double[psample_size];
    psample(d0, h0_gen, psample_size, p0, main_sample_size);
    double* F0 = new double[N]{};
    ecdf(p0, psample_size, GOOD_STEP_SIZE, F0);

    double* p1 = new double[psample_size];
    psample(d0, h1_gen, psample_size, p1, main_sample_size);
    double* F1 = new double[N]{};
    ecdf(p1, psample_size, GOOD_STEP_SIZE, F1);

    delete d0;
    delete[] p0;
    delete[] p1;
    delete[] F0;
    delete[] F1;
}


int get_pdist(double* &F0, double* &F1,
              PoisGen* h0_gen, PoisGen* h1_gen,
              int psample_size, int main_sample_size,
              double alpha, double &obs_sgnf_lvl, double &obs_pwr){
    int N = 1 / GOOD_STEP_SIZE;
    Distribution *d0 = new Distribution(h0_gen->_lambda);

    double* p0 = new double[psample_size];
    psample(d0, h0_gen, psample_size, p0, main_sample_size);
    F0 = new double[N]{};
    ecdf(p0, psample_size, GOOD_STEP_SIZE, F0);

    double* p1 = new double[psample_size];
    psample(d0, h1_gen, psample_size, p1, main_sample_size);
    F1 = new double[N]{};
    ecdf(p1, psample_size, GOOD_STEP_SIZE, F1);

    int ix = 0;
    if(alpha >= GOOD_STEP_SIZE){
        ix = alpha / GOOD_STEP_SIZE - 1 + EPS;
    }

    obs_sgnf_lvl = F0[ix];
    obs_pwr = F1[ix];

    delete d0;
    delete[] p0;
    delete[] p1;

    return N;
}


