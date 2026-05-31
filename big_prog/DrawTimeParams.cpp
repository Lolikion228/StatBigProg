#include "DrawTimeParams.h"

DrawTimeParams::DrawTimeParams(std::mt19937_64* stdgen):
    _stdgen(stdgen),
    lambda_min(1.0),
    lambda_max(30.0),
    cnt_steps(10),
    sample_size(90000),
    dur1(nullptr),
    dur2(nullptr)
{
    update_dur();
}

void DrawTimeParams::update_dur(){
    int* sample_1 = new int[sample_size]{};
    int* sample_2 = new int[sample_size]{};

    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;

    delete[] dur1;
    delete[] dur2;
    dur1 = new std::chrono::milliseconds[int(cnt_steps) + 1]{};
    dur2 = new std::chrono::milliseconds[int(cnt_steps) + 1]{};


    for(int i=0; i<=cnt_steps; ++i){
        double lambda = lambda_min + (i / cnt_steps) * (lambda_max - lambda_min);

        Distribution *d = new Distribution(lambda);
        PoisGenInvFunc *gen1 = new PoisGenInvFunc(d, _stdgen);
        PoisGenKnuth *gen2 = new PoisGenKnuth(d, _stdgen);

        start = std::chrono::high_resolution_clock::now();
        gen1->gen_sample(sample_size);
        end = std::chrono::high_resolution_clock::now();
        dur1[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        start = std::chrono::high_resolution_clock::now();
        gen2->gen_sample(sample_size);
        end = std::chrono::high_resolution_clock::now();
        dur2[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        delete d;
        delete gen1;
        delete gen2;
    }

    delete[] sample_1;
    delete[] sample_2;
}


DrawTimeParams::DrawTimeParams(const DrawTimeParams& other) :
    _stdgen(other._stdgen),
    lambda_min(other.lambda_min),
    lambda_max(other.lambda_max),
    cnt_steps(other.cnt_steps),
    sample_size(other.sample_size),
    dur1(nullptr),
    dur2(nullptr)
{
    int N = static_cast<int>(cnt_steps) + 1;

    if (other.dur1) {
        dur1 = new std::chrono::milliseconds[N];
        for (int i = 0; i < N; ++i) dur1[i] = other.dur1[i];
    }
    if (other.dur2) {
        dur2 = new std::chrono::milliseconds[N];
        for (int i = 0; i < N; ++i) dur2[i] = other.dur2[i];
    }
}


DrawTimeParams::DrawTimeParams(DrawTimeParams&& other):
    _stdgen(other._stdgen),
    lambda_min(other.lambda_min),
    lambda_max(other.lambda_max),
    cnt_steps(other.cnt_steps),
    sample_size(other.sample_size),
    dur1(other.dur1),
    dur2(other.dur2)
{
    other.dur1 = nullptr;
    other.dur2 = nullptr;
    other.cnt_steps = 0;
}


DrawTimeParams& DrawTimeParams::operator=(const DrawTimeParams& other) {
    if (this == &other) {
        return *this;
    }

    delete[] dur1;
    delete[] dur2;

    _stdgen = other._stdgen;
    lambda_min = other.lambda_min;
    lambda_max = other.lambda_max;
    cnt_steps = other.cnt_steps;
    sample_size = other.sample_size;

    int N = static_cast<int>(cnt_steps) + 1;

    if (other.dur1) {
        dur1 = new std::chrono::milliseconds[N];
        for (int i = 0; i < N; ++i) dur1[i] = other.dur1[i];
    } else {
        dur1 = nullptr;
    }

    if (other.dur2) {
        dur2 = new std::chrono::milliseconds[N];
        for (int i = 0; i < N; ++i) dur2[i] = other.dur2[i];
    } else {
        dur2 = nullptr;
    }

    return *this;
}




DrawTimeParams::~DrawTimeParams(){
    delete[] dur1;
    delete[] dur2;
}

