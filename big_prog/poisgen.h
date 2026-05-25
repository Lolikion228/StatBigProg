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
    PoisGen(Distribution* dist, std::mt19937_64* stdgen);
    virtual int gen() = 0;
    virtual ~PoisGen();
};

#endif // POISGEN_H
