#ifndef SETHISTGENPARAMSDIALOG_H
#define SETHISTGENPARAMSDIALOG_H

#include <QDialog>
#include "document.h"
#include <iostream>
namespace Ui {
class SetGenParamsDialog;
}

class SetHistGenParamsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetHistGenParamsDialog(Document *doc, QWidget *parent = nullptr);
    ~SetHistGenParamsDialog();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    double get_h1_lambda() const;
    int get_sample_size() const;
    int get_method_ix() const;

private:
    Ui::SetGenParamsDialog *ui;
};

#endif // SETHISTGENPARAMSDIALOG_H
