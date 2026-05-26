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
    //qDebug() << "here1";
    update_dur();
    //qDebug() << "here2";
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
        PoisGen1 *gen1 = new PoisGen1(d, _stdgen);
        PoisGen2 *gen2 = new PoisGen2(d, _stdgen);

        start = std::chrono::high_resolution_clock::now();
        // get_sample(sample_size, sample_1, gen1);
        gen1->gen_sample(sample_size);
        end = std::chrono::high_resolution_clock::now();
        dur1[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        start = std::chrono::high_resolution_clock::now();
        // get_sample(sample_size, sample_2, gen2);
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

DrawTimeParams::~DrawTimeParams(){
    delete[] dur1;
    delete[] dur2;
}

