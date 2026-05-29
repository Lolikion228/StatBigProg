#include "PDistGenParams.h"
#include <QDebug>

const int INIT_METHOD_IX = 1;
const double INIT_H0_LAMBDA = 20;
const double INIT_H1_LAMBDA = 20.5;

PDistGenParams::PDistGenParams(std::mt19937_64* stdgen):
    _stdgen(stdgen),
    psample_size(9999),
    main_sample_size(100),
    sgnf_level(0.15),
    obs_sgnf_level(0),
    obs_power(0),

    d0(nullptr),
    d1(nullptr),
    h0_gen(nullptr),
    h1_gen(nullptr),
    h0_sample(nullptr),
    h1_sample(nullptr)
{
    set_params(INIT_METHOD_IX,
               INIT_H0_LAMBDA,
               INIT_H1_LAMBDA);

    N = get_pdist(h0_gen, h1_gen,
              psample_size, main_sample_size,
              h0_sample, h1_sample, sgnf_level, obs_sgnf_level, obs_power);

}

void PDistGenParams::set_params(int method_ix,
                                double h0_lambda,
                                double h1_lambda){
    delete h0_gen;
    delete h1_gen;
    delete d0;
    delete d1;

    _method_ix = method_ix;
    _h0_lambda = h0_lambda;
    _h1_lambda = h1_lambda;

    d0 = new Distribution(h0_lambda);
    d1 = new Distribution(h1_lambda);

    if (method_ix==1){
        h0_gen = new PoisGen1(d0, _stdgen);
        h1_gen = new PoisGen1(d1, _stdgen);
    }
    if (method_ix==2){
        h0_gen = new PoisGen2(d0, _stdgen);
        h1_gen = new PoisGen2(d1, _stdgen);
    }
}

PDistGenParams::~PDistGenParams(){
    delete h0_gen;
    delete h1_gen;
    delete d0;
    delete d1;
    delete[] h0_sample;
    delete[] h1_sample;
}
