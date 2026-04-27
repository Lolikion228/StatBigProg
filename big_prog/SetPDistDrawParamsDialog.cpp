#include "SetPDistDrawParamsDialog.h"
#include "ui_SetPDistDrawParamsDialog.h"

SetPDistDrawParamsDialog::SetPDistDrawParamsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPDistDrawParamsDialog)
{
    ui->setupUi(this);
}

SetPDistDrawParamsDialog::~SetPDistDrawParamsDialog()
{
    delete ui;
}
