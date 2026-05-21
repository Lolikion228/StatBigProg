#include "mysample.h"
#include <limits>
#include <iostream>

MySample::MySample():
    _sample_size(0),
    _sample(nullptr)
{}

void MySample::set_sample(int* sample, int n){
    delete[] _sample;

    _sample = sample;
    _sample_size = n;

    _min_val=std::numeric_limits<int>::max();
    _max_val=-1;

    for(int i=0; i<n; ++i){
        if(_sample[i]>=_max_val) _max_val = _sample[i];
        if(_sample[i]<=_min_val) _min_val = _sample[i];
    }

}

int* MySample::get_sample() const{
    return _sample;
}

int MySample::get_sample_size() const{
    return _sample_size;
}

int MySample::get_min_val() const{
    return _min_val;
}

int MySample::get_max_val() const{
    return _max_val;
}

int MySample::get_range() const{
    return _range;
}


MySample::~MySample(){
    delete[] _sample;
}
