#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <iostream>
#include <cmath>
#include <QColor>
#include <random>
#include "poisgen1.h"
#include "poisgen2.h"
#include "mysample.h"
#include "utils.h"
#include "mod.h"
#include <QDebug>
#include "HistGenParams.h"
#include "PDistGenParams.h"



class Document
{
protected:

public:
    HistGenParams* hist_gen_params;
    PDistGenParams* pdist_gen_params;

    Document(std::mt19937_64* stdgen);
    ~Document();
};

#endif // DOCUMENT_H
