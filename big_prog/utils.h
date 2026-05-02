#ifndef UTILS_H
#define UTILS_H

#include <random>
#include "poisgen.h"
#include <QString>
#include <QMessageBox>

int check_dbl_field(double lb, double ub, QString desc, QString str);

int check_int_field(int lb, int ub, QString desc, QString str);

void get_sample(int N, int *X, PoisGen* absgen);

#endif // UTILS_H
