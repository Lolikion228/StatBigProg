#ifndef POISGEN2_H
#define POISGEN2_H

#include "poisgen.h"

class PoisGen2 : public PoisGen
{
public:
    PoisGen2(double lambda, std::mt19937_64* stdgen): PoisGen(lambda, stdgen){};
    int gen();
    ~PoisGen2(){};
};

#endif // POISGEN2_H
