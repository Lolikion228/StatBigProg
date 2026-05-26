#include "document.h"
#include <limits>


Document::Document(std::mt19937_64* stdgen):
    _stdgen(stdgen),
    hist_gen_params(new HistGenParams(stdgen)),
    pdist_gen_params(new PDistGenParams(stdgen))
    //draw_time_params(new DrawTimeParams(stdgen))
{

}


Document::~Document(){
    delete hist_gen_params;
    delete pdist_gen_params;
    //delete draw_time_params;
}


