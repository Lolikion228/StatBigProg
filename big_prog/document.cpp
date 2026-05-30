#include "document.h"
#include <limits>


Document::Document(std::mt19937_64* stdgen):
    _stdgen(stdgen),
    hist_gen_params(new HistGenParams(stdgen)),
    pdist_gen_params(new PDistGenParams(stdgen)),
    draw_time_params(new DrawTimeParams(stdgen))
{
}


Document::Document(const Document& other) :
    _stdgen(other._stdgen),
    hist_gen_params(nullptr),
    pdist_gen_params(nullptr),
    draw_time_params(nullptr)
{
    if (other.hist_gen_params) {
        hist_gen_params = new HistGenParams(*other.hist_gen_params);
    }
    if (other.pdist_gen_params) {
        pdist_gen_params = new PDistGenParams(*other.pdist_gen_params);
    }
    if (other.draw_time_params) {
        draw_time_params = new DrawTimeParams(*other.draw_time_params);
    }
}


Document::Document(Document&& other) :
    _stdgen(other._stdgen),
    hist_gen_params(other.hist_gen_params),
    pdist_gen_params(other.pdist_gen_params),
    draw_time_params(other.draw_time_params)
{
    other.hist_gen_params = nullptr;
    other.pdist_gen_params = nullptr;
    other.draw_time_params = nullptr;
}


Document& Document::operator=(const Document& other) {
    if (this == &other) {
        return *this;
    }

    delete hist_gen_params;
    delete pdist_gen_params;
    delete draw_time_params;

    _stdgen = other._stdgen;

    hist_gen_params  = other.hist_gen_params  ? new HistGenParams(*other.hist_gen_params)   : nullptr;
    pdist_gen_params = other.pdist_gen_params ? new PDistGenParams(*other.pdist_gen_params) : nullptr;
    draw_time_params = other.draw_time_params ? new DrawTimeParams(*other.draw_time_params) : nullptr;

    return *this;
}


Document::~Document(){
    delete hist_gen_params;
    delete pdist_gen_params;
    delete draw_time_params;
}


