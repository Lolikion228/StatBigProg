#include "document.h"
#include <limits>


Document::Document(std::mt19937_64* stdgen):
    hist_gen_params(new HistGenParams(stdgen)),
    pdist_gen_params(new PDistGenParams(stdgen))
{

}


Document::~Document(){
//    delete hist_gen_params;
}


