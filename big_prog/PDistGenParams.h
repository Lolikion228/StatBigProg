#ifndef PDISTGENPARAMS_H
#define PDISTGENPARAMS_H

#include "poisgen.h"
#include "poisgen1.h"
#include "mod.h"

class PDistGenParams
{
public:
    int method_ix;
    int psample_size;
    int main_sample_size;
    double h0_lambda;
    double h1_lambda;
    PoisGen* h0_gen;
    PoisGen* h1_gen;
    int N;
    double* h0_sample;
    double* h1_sample;

    PDistGenParams(std::mt19937_64* stdgen);
    ~PDistGenParams();
};

#endif // PDISTGENPARAMS_H
