#ifndef SETPDISTGENPARAMSDIALOG_H
#define SETPDISTGENPARAMSDIALOG_H

#include <QDialog>
#include "document.h"
#include <QMessageBox>

namespace Ui {
class SetPDistGenParamsDialog;
}

class SetPDistGenParamsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetPDistGenParamsDialog(Document* doc, QWidget *parent = nullptr);
    ~SetPDistGenParamsDialog();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    double get_h0_lambda() const;
    double get_h1_lambda() const;
    int get_psample_size() const;
    int get_main_sample_size() const;
    int get_method_ix() const;

private:
    Ui::SetPDistGenParamsDialog *ui;
};

#endif // SETPDISTGENPARAMSDIALOG_H
