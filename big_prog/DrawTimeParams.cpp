#include "DrawTimeParams.h"

DrawTimeParams::DrawTimeParams(std::mt19937_64* stdgen):
    _stdgen(stdgen),
    lambda_min(1.0),
    lambda_max(40.0),
    cnt_steps(13),
    sample_size(100000)
{

}

DrawTimeParams::~DrawTimeParams(){

}

