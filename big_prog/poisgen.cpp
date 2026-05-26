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


PoisGen::~PoisGen(){
    delete[] _sample;
}




