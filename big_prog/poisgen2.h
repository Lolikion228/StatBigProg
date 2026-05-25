#ifndef POISGEN2_H
#define POISGEN2_H

#include "poisgen.h"

class PoisGen2 : public PoisGen
{
public:
    PoisGen2(Distribution *dist, std::mt19937_64* stdgen):
        PoisGen(dist, stdgen){}
    int gen();
    ~PoisGen2(){}
};

#endif // POISGEN2_H
