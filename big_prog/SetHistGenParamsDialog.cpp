#include "SetHistGenParamsDialog.h"
#include "ui_setgenparamsdialog.h"
#include <QMessageBox>

SetHistGenParamsDialog::SetHistGenParamsDialog(Document *doc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetGenParamsDialog)
{
    ui->setupUi(this);

    // init
    ui->h1_lambda_edit->setText(QString::number(doc->hist_gen_params->h1_lambda));
    ui->sample_size_edit->setText(QString::number(doc->hist_gen_params->sample->get_sample_size()));
    int m_ix = doc->hist_gen_params->method_ix;
    ui->method1_button->setChecked(m_ix == 1);
    ui->method2_button->setChecked(m_ix == 2);

    ui->buttonBox->disconnect();
    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &SetHistGenParamsDialog::on_buttonBox_accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            this, &SetHistGenParamsDialog::on_buttonBox_rejected);
}


double SetHistGenParamsDialog::get_h1_lambda() const{
    return ui->h1_lambda_edit->text().toDouble();
}

int SetHistGenParamsDialog::get_sample_size() const{
    return ui->sample_size_edit->text().toInt();
}

int SetHistGenParamsDialog::get_method_ix() const{
    if(ui->method1_button->isChecked()){
        return 1;
    }
    else{
        return 2;
    }
}


void SetHistGenParamsDialog::on_buttonBox_accepted()
{
    QString ss_txt = ui->sample_size_edit->text();
    QString lambda_txt = ui->h1_lambda_edit->text();


    if (ss_txt.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Вы не ввели размер выборки!");
        return;
    }
    if (lambda_txt.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Вы не ввели лямбду!");
        return;
    }

    bool ss_ok;
    int number = ss_txt.toInt(&ss_ok);
    if ( (!ss_ok) || (number < 2 || number > 100000) ) {
        QMessageBox::warning(this, "Ошибка",
                            QString("Размер выборки - целое число от %1 до %2!")
                            .arg(2).arg(100000));
        return;
    }


    bool lambda_ok;
    double lm = lambda_txt.toDouble(&lambda_ok);
    if ( (!lambda_ok) || (lm < 2 || lm > 100) ) {
        QMessageBox::warning(this, "Ошибка",
                            QString("Lambda - число от %1 до %2!")
                            .arg(2).arg(100));
        return;
    }

    accept();
}


void SetHistGenParamsDialog::on_buttonBox_rejected()
{
    reject();
}


SetHistGenParamsDialog::~SetHistGenParamsDialog()
{
    delete ui;
}
