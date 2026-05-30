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


PDistGenParams::PDistGenParams(const PDistGenParams& other) :
    _stdgen(other._stdgen),
    _method_ix(other._method_ix),
    psample_size(other.psample_size),
    main_sample_size(other.main_sample_size),
    _h0_lambda(other._h0_lambda),
    _h1_lambda(other._h1_lambda),
    sgnf_level(other.sgnf_level),
    obs_sgnf_level(other.obs_sgnf_level),
    obs_power(other.obs_power),
    N(other.N),
    d0(nullptr), d1(nullptr),
    h0_gen(nullptr), h1_gen(nullptr),
    h0_sample(nullptr), h1_sample(nullptr)
{
    if (other.d0) d0 = new Distribution(*other.d0);
    if (other.d1) d1 = new Distribution(*other.d1);

    if (other.h0_gen) {
        if (_method_ix == 1) h0_gen = new PoisGen1(*static_cast<PoisGen1*>(other.h0_gen));
        else if (_method_ix == 2) h0_gen = new PoisGen2(*static_cast<PoisGen2*>(other.h0_gen));
    }
    if (other.h1_gen) {
        if (_method_ix == 1) h1_gen = new PoisGen1(*static_cast<PoisGen1*>(other.h1_gen));
        else if (_method_ix == 2) h1_gen = new PoisGen2(*static_cast<PoisGen2*>(other.h1_gen));
    }

    if (other.h0_sample && N > 0) {
        h0_sample = new double[N];
        for (int i = 0; i < N; ++i) h0_sample[i] = other.h0_sample[i];
    }
    if (other.h1_sample && N > 0) {
        h1_sample = new double[N];
        for (int i = 0; i < N; ++i) h1_sample[i] = other.h1_sample[i];
    }
}


PDistGenParams::PDistGenParams(PDistGenParams&& other) :
    _stdgen(other._stdgen),
    _method_ix(other._method_ix),
    psample_size(other.psample_size),
    main_sample_size(other.main_sample_size),
    _h0_lambda(other._h0_lambda),
    _h1_lambda(other._h1_lambda),
    sgnf_level(other.sgnf_level),
    obs_sgnf_level(other.obs_sgnf_level),
    obs_power(other.obs_power),
    N(other.N),
    d0(other.d0),
    d1(other.d1),
    h0_gen(other.h0_gen),
    h1_gen(other.h1_gen),
    h0_sample(other.h0_sample),
    h1_sample(other.h1_sample)
{
    other.d0 = nullptr;
    other.d1 = nullptr;
    other.h0_gen = nullptr;
    other.h1_gen = nullptr;
    other.h0_sample = nullptr;
    other.h1_sample = nullptr;
    other.N = 0;
}


PDistGenParams& PDistGenParams::operator=(const PDistGenParams& other) {
    if (this == &other) return *this;

    delete h0_gen;
    delete h1_gen;
    delete d0;
    delete d1;
    delete[] h0_sample;
    delete[] h1_sample;

    _stdgen = other._stdgen;
    _method_ix = other._method_ix;
    psample_size = other.psample_size;
    main_sample_size = other.main_sample_size;
    _h0_lambda = other._h0_lambda;
    _h1_lambda = other._h1_lambda;
    sgnf_level = other.sgnf_level;
    obs_sgnf_level = other.obs_sgnf_level;
    obs_power = other.obs_power;
    N = other.N;

    d0 = other.d0 ? new Distribution(*other.d0) : nullptr;
    d1 = other.d1 ? new Distribution(*other.d1) : nullptr;

    if (other.h0_gen) {
        if (_method_ix == 1) h0_gen = new PoisGen1(*static_cast<PoisGen1*>(other.h0_gen));
        else if (_method_ix == 2) h0_gen = new PoisGen2(*static_cast<PoisGen2*>(other.h0_gen));
    } else h0_gen = nullptr;

    if (other.h1_gen) {
        if (_method_ix == 1) h1_gen = new PoisGen1(*static_cast<PoisGen1*>(other.h1_gen));
        else if (_method_ix == 2) h1_gen = new PoisGen2(*static_cast<PoisGen2*>(other.h1_gen));
    } else h1_gen = nullptr;

    if (other.h0_sample && N > 0) {
        h0_sample = new double[N];
        for (int i = 0; i < N; ++i) h0_sample[i] = other.h0_sample[i];
    } else h0_sample = nullptr;

    if (other.h1_sample && N > 0) {
        h1_sample = new double[N];
        for (int i = 0; i < N; ++i) h1_sample[i] = other.h1_sample[i];
    } else h1_sample = nullptr;

    return *this;
}


PDistGenParams::~PDistGenParams(){
    delete h0_gen;
    delete h1_gen;
    delete d0;
    delete d1;
    delete[] h0_sample;
    delete[] h1_sample;
}
