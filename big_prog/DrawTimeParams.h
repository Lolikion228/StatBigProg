#ifndef DRAWTIMEPARAMS_H
#define DRAWTIMEPARAMS_H

#include <chrono>
#include <random>
#include "poisgen1.h"
#include "poisgen2.h"
#include "utils.h"

class DrawTimeParams
{
public:
    std::mt19937_64* _stdgen;
    double lambda_min;
    double lambda_max;
    double cnt_steps;
    int sample_size;
//    std::chrono::milliseconds* dur1;
//    std::chrono::milliseconds* dur2;
    DrawTimeParams(std::mt19937_64* stdgen);
    ~DrawTimeParams();
};

#endif // DRAWTIMEPARAMS_H
