#include "poisgen.h"


PoisGen::PoisGen(Distribution *dist, std::mt19937_64* stdgen):
    _dist(dist),
    _stdgen(stdgen),
    _lambda(dist->get_lambda()),
    _min_val(0),
    _max_val(0),
    _sample_size(0),
    _sample(nullptr)
{

}


void PoisGen::gen_sample(int n){
    delete[] _sample;
    _sample_size = n;
    _min_val = std::numeric_limits<int>::max();
    _max_val = -1;
    _sample = new int[_sample_size]{};
    for(int i=0; i<n; ++i){
        _sample[i] = gen();
    }

    for(int i=0; i<n; ++i){
        if(_sample[i] >= _max_val) _max_val = _sample[i];
        if(_sample[i] <= _min_val) _min_val = _sample[i];
    }
}

PoisGen::PoisGen(const PoisGen& other):
    _dist(other._dist),
    _stdgen(other._stdgen),
    _lambda(other._lambda),
    _min_val(other._min_val),
    _max_val(other._max_val),
    _sample_size(other._sample_size),
    _sample(nullptr)
{
    if (other._sample && _sample_size > 0) {
        _sample = new int[_sample_size];
        for (int i = 0; i < _sample_size; ++i) {
            _sample[i] = other._sample[i];
        }
    }
}


PoisGen::PoisGen(PoisGen&& other):
    _dist(other._dist),
    _stdgen(other._stdgen),
    _lambda(other._lambda),
    _min_val(other._min_val),
    _max_val(other._max_val),
    _sample_size(other._sample_size),
    _sample(other._sample)
{
    other._sample = nullptr;
    other._sample_size = 0;
}

PoisGen& PoisGen::operator=(const PoisGen& other) {
    if (this == &other) {
        return *this;
    }

    delete[] _sample;

    _dist = other._dist;
    _stdgen = other._stdgen;
    _lambda = other._lambda;
    _min_val = other._min_val;
    _max_val = other._max_val;
    _sample_size = other._sample_size;

    if (other._sample && _sample_size > 0) {
        _sample = new int[_sample_size];
        for (int i = 0; i < _sample_size; ++i) {
            _sample[i] = other._sample[i];
        }
    }
    else {
        _sample = nullptr;
    }

    return *this;
}


PoisGen::~PoisGen(){
    delete[] _sample;
}




