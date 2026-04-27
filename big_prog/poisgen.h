#ifndef POISGEN_H
#define POISGEN_H
#include <random>

class PoisGen
{
protected:

    std::mt19937_64* _stdgen;
public:
    double _lambda;
    PoisGen(double lambda, std::mt19937_64* stdgen);
    virtual int gen() = 0;
    virtual ~PoisGen();
};

#endif // POISGEN_H
