#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <iostream>
#include <cmath>
#include <QColor>
#include <random>
#include "poisgen1.h"
#include "poisgen2.h"
#include "utils.h"
#include "mod.h"
#include <QDebug>
#include "HistGenParams.h"
#include "PDistGenParams.h"
#include "DrawTimeParams.h"


class Document
{
protected:

public:
    std::mt19937_64* _stdgen;
    HistGenParams* hist_gen_params;
    PDistGenParams* pdist_gen_params;
    DrawTimeParams* draw_time_params;

    Document(std::mt19937_64* stdgen);
    ~Document();
};

#endif // DOCUMENT_H
