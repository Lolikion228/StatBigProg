#ifndef HISTGENPARAMS_H
#define HISTGENPARAMS_H

#include "poisgen.h"
#include "poisgen1.h"
#include "poisgen2.h"
#include "utils.h"

class HistGenParams{
   private:
    Distribution *_dist;
    std::mt19937_64* _stdgen;
   public:
    double h1_lambda;
    int _method_ix;
    PoisGen* curr_gen;

    HistGenParams(std::mt19937_64* stdgen);
    void set_params(double lambda, int method_ix);
    ~HistGenParams();
};

#endif // HISTGENPARAMS_H
