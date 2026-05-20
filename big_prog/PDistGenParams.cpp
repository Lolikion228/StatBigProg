#include "PDistGenParams.h"

PDistGenParams::PDistGenParams(std::mt19937_64* stdgen):
    method_ix(1),
    psample_size(1000),
    main_sample_size(100),
    h0_lambda(20),
    h1_lambda(20.5),
    sgnf_level(0.15),
    obs_sgnf_level(0),
    obs_power(0),

    h0_sample(nullptr),
    h1_sample(nullptr)
{
    h0_gen = new PoisGen1(h0_lambda, stdgen);
    h1_gen = new PoisGen1(h1_lambda, stdgen);
    N = get_pdist(h0_gen, h1_gen,
              psample_size, main_sample_size,
              h0_sample, h1_sample, sgnf_level, obs_sgnf_level, obs_power);
}

PDistGenParams::~PDistGenParams(){
    delete h0_gen;
    delete h1_gen;
    delete[] h0_sample;
    delete[] h1_sample;
}
