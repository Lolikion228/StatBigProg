#include "HistGenParams.h"
#include <QDebug>

const int INIT_SAMPLE_SIZE = 50;
const double INIT_LAMBDA = 10.0;

HistGenParams::HistGenParams(std::mt19937_64* stdgen):
    _method_ix(1),
    _dist(nullptr),
    curr_gen(nullptr),
    _stdgen(stdgen)
{
    set_params(INIT_LAMBDA, _method_ix);
    curr_gen->gen_sample(INIT_SAMPLE_SIZE);
}

void HistGenParams::set_params(double lambda, int method_ix){
    delete curr_gen;
    delete _dist;

    _method_ix = method_ix;
    h1_lambda = lambda;
    _dist = new Distribution(h1_lambda);

    if (_method_ix==1){
        curr_gen = new PoisGen1(_dist, _stdgen);
    }
    if (_method_ix==2){
        curr_gen = new PoisGen2(_dist, _stdgen);
    }
}

HistGenParams::~HistGenParams(){
    delete curr_gen;
    delete _dist;
}
