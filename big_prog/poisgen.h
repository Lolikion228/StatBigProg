#ifndef POISGEN_H
#define POISGEN_H
#include <random>
#include "distribution.h"

class PoisGen
{
protected:
    Distribution *_dist;
    std::mt19937_64* _stdgen;

public:
    double _lambda;
    int _min_val;
    int _max_val;
    int _sample_size;
    int* _sample;
    PoisGen(Distribution* dist, std::mt19937_64* stdgen);
    void gen_sample(int n);
    virtual int gen() = 0;
    ~PoisGen();
};

#endif // POISGEN_H
