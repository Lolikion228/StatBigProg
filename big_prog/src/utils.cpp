#include "utils.h"



int check_dbl_field(double lb, double ub, QString desc, QString str){
    if (str.isEmpty()) {
        QMessageBox::warning(nullptr, "Ошибка", QString("Вы не ввели %1!").arg(desc));
        return 1;
    }

    bool dbl_ok;
    double number = str.toDouble(&dbl_ok);

    if ( (!dbl_ok) || (number < lb || number > ub) ) {
        QMessageBox::warning(nullptr, "Ошибка",
                            QString("%3 - число от %1 до %2!")
                            .arg(lb).arg(ub).arg(desc));
        return 1;
    }

    return 0;
}

int check_int_field(int lb, int ub, QString desc, QString str){
    if (str.isEmpty()) {
        QMessageBox::warning(nullptr, "Ошибка", QString("Вы не ввели %1!").arg(desc));
        return 1;
    }

    bool int_ok;
    int number = str.toInt(&int_ok);

    if ( (!int_ok) || (number < lb || number > ub) ) {
        QMessageBox::warning(nullptr, "Ошибка",
                            QString("%3 - целое число от %1 до %2!")
                            .arg(lb).arg(ub).arg(desc));
        return 1;
    }

    return 0;
}

