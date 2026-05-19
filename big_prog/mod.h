#ifndef MOD_H
#define MOD_H

#include "funcs.h"
#include "poisgen.h"
#include "probdist.h"
#include "utils.h"

double pval(double h0_param, PoisGen* h1_gen, int sample_size, int verbose);


void psample(double h0_param, PoisGen* h1_gen, int psample_size,
             double *X, int main_sample_size);


void pecdf(PoisGen* h0_gen, PoisGen* h1_gen, double alpha,
           int psample_size, int main_sample_size);

void ecdf(double *X, int N, double step_size, double *F);

int get_pdist(PoisGen* h0_gen, PoisGen* h1_gen,
              int psample_size, int main_sample_size,
              double* &F0, double* &F1);

int get_pdist(PoisGen* h0_gen, PoisGen* h1_gen,
              int psample_size, int main_sample_size,
              double* &F0, double* &F1, double alpha, double &obs_sgnf_lvl, double &obs_pwr);


#endif // MOD_H
