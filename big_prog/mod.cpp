#include "mod.h"
#include "QDebug"
const double GOOD_STEP_SIZE = 0.05;
const double GOOD_CUM_EXP_FREQ_THRESH = 5.0;
const double EPS = 1e-6;
const double ALMOST_ONE = 1.0 - EPS;


double pval(Distribution d0, PoisGen* h1_gen, int sample_size, int verbose){
    double h0_param = d0.get_lambda();
    int X[sample_size];
    get_sample(sample_size, X, h1_gen);

    int right_lim = h0_param + 3 * sqrt(h0_param);
    double p[right_lim];
    double t = exp(-h0_param);
    double sum = t;
    p[0] = t;
    for(int i=1; i<right_lim; ++i){
        t *= h0_param / i;
        p[i] = t;
        sum += p[i];
    }
    p[right_lim - 1] += (1 - sum);

    MySample *sample = new MySample;
    sample->set_sample(X, sample_size);
    ChiSq test(sample, &d0);

    double res1 = 1 - pChi(test._stat, test._df);

    return std::min(res1, ALMOST_ONE);
}

void psample(Distribution d0, PoisGen* h1_gen, int psample_size,
             double *X, int main_sample_size){
    for(int i=0; i<psample_size; ++i)
        X[i] = pval(d0, h1_gen, main_sample_size, 0);
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
    Distribution d0 = Distribution(h0_gen->_lambda);

    double* p0 = new double[psample_size];
    psample(d0, h0_gen, psample_size, p0, main_sample_size);
    double* F0 = new double[N]{};
    ecdf(p0, psample_size, GOOD_STEP_SIZE, F0);

    double* p1 = new double[psample_size];
    psample(d0, h1_gen, psample_size, p1, main_sample_size);
    double* F1 = new double[N]{};
    ecdf(p1, psample_size, GOOD_STEP_SIZE, F1);

    std::cout << "pval     F0     F1\n";
    for(int i=0; i<N; ++i){
        printf("%3.2f  %5.3f  %5.3f\n", GOOD_STEP_SIZE*(i+1), F0[i], F1[i]);
    }

    std::cout << "\n";
    printf("on alpha = %.3f\n", alpha);
    int ix = 0;
    if(alpha >= GOOD_STEP_SIZE){
        ix = alpha / GOOD_STEP_SIZE - 1 + EPS;
    }
    printf("ERR_1 = %.3f   POW = %.3f\n", F0[ix], F1[ix]);


    delete[] p0;
    delete[] p1;
    delete[] F0;
    delete[] F1;
}


int get_pdist(PoisGen* h0_gen, PoisGen* h1_gen,
              int psample_size, int main_sample_size,
              double* &F0, double* &F1, double alpha, double &obs_sgnf_lvl, double &obs_pwr){

    int N = 1 / GOOD_STEP_SIZE;
    Distribution d0 = Distribution(h0_gen->_lambda);

    double* p0 = new double[psample_size];
    psample(d0, h0_gen, psample_size, p0, main_sample_size);//bad
    F0 = new double[N]{};
    ecdf(p0, psample_size, GOOD_STEP_SIZE, F0);

    double* p1 = new double[psample_size];
    psample(d0, h1_gen, psample_size, p1, main_sample_size);
    F1 = new double[N]{};
    ecdf(p1, psample_size, GOOD_STEP_SIZE, F1);

//    double alpha=0.15;
    qDebug() << "at alpha = " << alpha;
    int ix = 0;
    if(alpha >= GOOD_STEP_SIZE){
        ix = alpha / GOOD_STEP_SIZE - 1 + EPS;
    }
    qDebug() << "err_1 = " << F0[ix];
    qDebug() << "pow = " << F1[ix];
    qDebug() << "\n";

    obs_sgnf_lvl = F0[ix];
    obs_pwr = F1[ix];

    delete[] p0;
    delete[] p1;
    return N;
}


