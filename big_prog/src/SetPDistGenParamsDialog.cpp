#include "SetPDistGenParamsDialog.h"
#include "ui_SetPDistGenParamsDialog.h"

SetPDistGenParamsDialog::SetPDistGenParamsDialog(Document* doc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPDistGenParamsDialog)
{
    ui->setupUi(this);

    ui->main_sample_size_lineEdit->setText(
                QString::number(doc->pdist_gen_params->main_sample_size));
    ui->psample_size_lineEdit->setText(
                QString::number(doc->pdist_gen_params->psample_size));
    ui->h0_lambda_lineEdit->setText(
                QString::number(doc->pdist_gen_params->_h0_lambda));
    ui->h1_lambda_lineEdit->setText(
                QString::number(doc->pdist_gen_params->_h1_lambda));
    ui->alpha_lineEdit->setText(
                QString::number(doc->pdist_gen_params->sgnf_level));
    int m_ix = doc->pdist_gen_params->_method_ix;
    ui->method_1_button->setChecked(m_ix == 1);
    ui->method_2_button->setChecked(m_ix == 2);

    ui->buttonBox->disconnect();
    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &SetPDistGenParamsDialog::on_buttonBox_accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            this, &SetPDistGenParamsDialog::on_buttonBox_rejected);

}


int SetPDistGenParamsDialog::get_psample_size() const{
    return ui->psample_size_lineEdit->text().toInt();
}

int SetPDistGenParamsDialog::get_main_sample_size() const{
    return ui->main_sample_size_lineEdit->text().toInt();
}

double SetPDistGenParamsDialog::get_h0_lambda() const{
    return ui->h0_lambda_lineEdit->text().toDouble();
}

double SetPDistGenParamsDialog::get_h1_lambda() const{
    return ui->h1_lambda_lineEdit->text().toDouble();
}

double SetPDistGenParamsDialog::get_sgnfc_level() const{
    return ui->alpha_lineEdit->text().toDouble();
}

int SetPDistGenParamsDialog::get_method_ix() const{
    if(ui->method_1_button->isChecked()){
        return 1;
    }
    else{
        return 2;
    }
}



void SetPDistGenParamsDialog::on_buttonBox_accepted()
{
    int res = 0;
    res += check_int_field(10, 10000, QString("размер главной выборки"),
                    ui->main_sample_size_lineEdit->text());

    res += check_int_field(10, 10000, QString("размер выборки pval"),
                    ui->psample_size_lineEdit->text());

    res += check_dbl_field(0.1, 100, QString("H0 lambda"),
                    ui->h0_lambda_lineEdit->text());

    res += check_dbl_field(0.1, 100, QString("H1 lambda"),
                    ui->h1_lambda_lineEdit->text());

    res += check_dbl_field(0.001, 0.99, QString("sgnfc level"),
                    ui->alpha_lineEdit->text());

    if(res != 0){
        return;
    }

    accept();
}


void SetPDistGenParamsDialog::on_buttonBox_rejected()
{
    reject();
}

SetPDistGenParamsDialog::~SetPDistGenParamsDialog()
{
    delete ui;
}
