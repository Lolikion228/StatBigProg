#include "funcs.h"
#include <QDebug>

void sep(char c, int n, int m){
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            std::cout << c;
        }
        std::cout << "\n";
    }

}


template <typename T>
double sum_arr(T x, int n){
    double sum = 0;
    for(int i=0; i<n; ++i){
        sum += x[i];
    }
    return sum;
}


double dchsisq(double t, int k){
    double c = pow(0.5, k / 2.) / std::tgamma(k / 2.);
    return c * pow(t, k / 2. - 1) * exp(-t / 2.);
}


void get_freqs(double *obs_freq, double *exp_freq, double *p, int *X, int N, int sample_size){
    for(int i=0; i<sample_size; ++i){
        if( X[i] >= (N - 1) ) {
            ++obs_freq[N - 1];
        }
        else {
            ++obs_freq[ X[i] ];
        }
    }

    for(int i=0; i<N; ++i){
        exp_freq[i] = sample_size * p[i];
    }
}


void big_print(double *obs_freq, double *exp_freq, double *diff_hist, double *summand_hist,
               double *cum_exp_freq_hist, double *cum_exp_freq_all_hist,
               int N, int sample_size, bool make_groups){

    sep('#', 1, 72);
    std::cout << "right_lim = " << N - 1 << "\n";
    std::cout << "sample_size = " << sample_size << "\n";
    // std::cout<< "obs_freq_sum = " << sum_arr(obs_freq, N) << "\n";
    // std::cout<< "exp_freq_sum = " << sum_arr(exp_freq, N) << "\n";
    sep('#', 1, 72);
    std::cout <<"\n";

    sep('#', 1, 72);
    if(make_groups){
        std::cout << " i  obs_freq  exp_freq  cum_exp_freq  cum_exp_freq_all  diff  summand\n";
        sep('#', 1, 72);
        for(int i=0; i<N; ++i){
            printf("%2d  %8.1f  %8.2f  %12.2f %17.2f %5.2f  %7.2f\n",
                i, obs_freq[i], exp_freq[i], cum_exp_freq_hist[i], cum_exp_freq_all_hist[i],
                diff_hist[i], summand_hist[i]);
            if(diff_hist[i] != 0){
                sep('-', 1, 72);
            }
        }
    }
    else{
        std::cout << " i  obs_freq  exp_freq    diff  summand\n";
        sep('#', 1, 52);
        for(int i=0; i<N; ++i){
            printf("%2d  %8.1f  %8.2f  %6.2f  %7.2f\n",
                i, obs_freq[i], exp_freq[i],
                diff_hist[i], summand_hist[i]);
            if(diff_hist[i] != 0){
                sep('-', 1, 52);
            }
        }
    }
    sep('#', 1, 72);
    std::cout << "\n";
}

// move 2 chisq class
// change int* to sample
double chisq_stat(int *X, int sample_size, double cum_exp_freq_thresh,
                  const Distribution &d0, int &dfs, double *&obs_freq,
                  double *&exp_freq, int &cnt_states){

    double res = 0;
    cnt_states = d0.get_lim(sample_size, cum_exp_freq_thresh);
    double* p = new double[cnt_states]{};
    d0.get_probs(cnt_states, p);

    obs_freq = new double[cnt_states]{};
    exp_freq = new double[cnt_states]{};

    double cum_exp_freq = 0;
    double cum_obs_freq = 0;
    double diff;
    double summand;
    int cnt_groups = 0;

    //можно убрать (в момент создания chisq)
    get_freqs(obs_freq, exp_freq, p, X, cnt_states, sample_size);

    // переименовать N
    for(int i=0; i<cnt_states; ++i){
        cum_obs_freq += obs_freq[i];
        cum_exp_freq += exp_freq[i];
        if(cum_exp_freq >= cum_exp_freq_thresh){
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

    dfs = cnt_groups - 1;

    delete[] p;

    return res;
}

