#ifndef FUNCS_H
#define FUNCS_H

#include <cmath>
#include <iostream>
#include "distribution.h"



/*
X: sample
p: vector of probs
N: size of p
*/

double chisq_stat(int *X, int sample_size, int verbose, double cum_exp_freq_thresh,
                 Distribution d0, int &dfs, double *&obs_freq, double *&exp_freq, int &N);

template <typename T>
void print_arr(T x, int n){
    std::cout << "[" ;
    for(int i=0; i<n; ++i){
        std::cout << x[i] << " ";
    }
    std::cout << "]\n";
}

#endif // FUNCS_H
