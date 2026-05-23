#include "HistGenParams.h"


const int INIT_SAMPLE_SIZE = 50;

HistGenParams::HistGenParams(std::mt19937_64* stdgen):
    h1_lambda(10),
    method_ix(1)
{
    curr_gen = new PoisGen1(h1_lambda, stdgen);

    int* _sample = new int[INIT_SAMPLE_SIZE];
    get_sample(INIT_SAMPLE_SIZE, _sample, curr_gen);
    sample = new MySample(_sample, INIT_SAMPLE_SIZE);
}

HistGenParams::~HistGenParams(){
    delete sample;
    delete curr_gen;
}
