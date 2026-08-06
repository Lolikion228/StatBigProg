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
        curr_gen = new PoisGenInvFunc(_dist, _stdgen);
    }
    if (_method_ix==2){
        curr_gen = new PoisGenKnuth(_dist, _stdgen);
    }
}



HistGenParams::HistGenParams(const HistGenParams& other) :
    _dist(nullptr),
    _stdgen(other._stdgen),
    h1_lambda(other.h1_lambda),
    _method_ix(other._method_ix),
    curr_gen(nullptr)
{
    if (other._dist) {
        _dist = new Distribution(*other._dist);
    }

    if (other.curr_gen) {
        if (_method_ix == 1) {
            curr_gen = new PoisGenInvFunc(*static_cast<PoisGenInvFunc*>(other.curr_gen));
        } else if (_method_ix == 2) {
            curr_gen = new PoisGenKnuth(*static_cast<PoisGenKnuth*>(other.curr_gen));
        }
    }
}


HistGenParams::HistGenParams(HistGenParams&& other):
    _dist(other._dist),
    _stdgen(other._stdgen),
    h1_lambda(other.h1_lambda),
    _method_ix(other._method_ix),
    curr_gen(other.curr_gen)
{
    other._dist = nullptr;
    other.curr_gen = nullptr;
}


HistGenParams& HistGenParams::operator=(const HistGenParams& other) {
    if (this == &other) {
        return *this;
    }

    delete curr_gen;
    delete _dist;

    _stdgen = other._stdgen;
    h1_lambda = other.h1_lambda;
    _method_ix = other._method_ix;

    _dist = other._dist ? new Distribution(*other._dist) : nullptr;

    if (other.curr_gen) {
        if (_method_ix == 1) {
            curr_gen = new PoisGenInvFunc(*static_cast<PoisGenInvFunc*>(other.curr_gen));
        } else if (_method_ix == 2) {
            curr_gen = new PoisGenKnuth(*static_cast<PoisGenKnuth*>(other.curr_gen));
        }
    } else {
        curr_gen = nullptr;
    }

    return *this;
}




HistGenParams::~HistGenParams(){
    delete curr_gen;
    delete _dist;
}
