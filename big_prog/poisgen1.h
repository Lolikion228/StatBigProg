#ifndef POISGEN1_H
#define POISGEN1_H

#include "poisgen.h"

class PoisGen1 : public PoisGen
{
public:
    PoisGen1(Distribution *dist, std::mt19937_64* stdgen):
        PoisGen(dist, stdgen){}
    int gen();
};

#endif // POISGEN1_H
