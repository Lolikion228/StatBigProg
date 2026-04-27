#ifndef POISGEN1_H
#define POISGEN1_H

#include "poisgen.h"

class PoisGen1 : public PoisGen
{
public:
    PoisGen1(double lambda, std::mt19937_64* stdgen): PoisGen(lambda, stdgen){};
    int gen();
    ~PoisGen1(){};
};

#endif // POISGEN1_H
