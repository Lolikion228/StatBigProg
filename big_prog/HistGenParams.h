#ifndef HISTGENPARAMS_H
#define HISTGENPARAMS_H

#include "poisgen.h"
#include "mysample.h"
#include "poisgen1.h"
#include "utils.h"

class HistGenParams{
   public:
    double h1_lambda;
    int method_ix;
    PoisGen* curr_gen;
    MySample* sample;

    HistGenParams(std::mt19937_64* stdgen);
    ~HistGenParams();
};

#endif // HISTGENPARAMS_H
