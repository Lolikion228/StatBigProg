#ifndef PDISTGENPARAMS_H
#define PDISTGENPARAMS_H

#include "poisgen.h"
#include "poisgen1.h"
#include "poisgen2.h"
#include "distribution.h"
#include "mod.h"

class PDistGenParams
{
public:
    std::mt19937_64* _stdgen;
    int _method_ix;
    int psample_size;
    int main_sample_size;
    double _h0_lambda;
    double _h1_lambda;

    double sgnf_level;
    double obs_sgnf_level;
    double obs_power;

    Distribution *d0;
    Distribution *d1;
    PoisGen* h0_gen;
    PoisGen* h1_gen;
    int N;
    double* h0_sample;
    double* h1_sample;

    PDistGenParams(std::mt19937_64* stdgen);
    PDistGenParams(const PDistGenParams& other);
    PDistGenParams(PDistGenParams&& other);
    PDistGenParams& operator=(const PDistGenParams& other);
    ~PDistGenParams();

    void set_params(int method_ix,
                    double h0_lambda,
                    double h1_lambda);

};

#endif // PDISTGENPARAMS_H
