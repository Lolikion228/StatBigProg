#include "DrawTimeDialog.h"
#include "ui_DrawTimeDialog.h"

DrawTimeDialog::DrawTimeDialog(QWidget *parent, DrawTimeParams* draw_time_params) :
    QDialog(parent),
    ui(new Ui::DrawTimeDialog)
{
    ui->setupUi(this);

    ui->lambda_min_lineEdit->setText(QString::number(draw_time_params->lambda_min));
    ui->lambda_max_lineEdit_2->setText(QString::number(draw_time_params->lambda_max));
    ui->sample_size_lineEdit_3->setText(QString::number(draw_time_params->sample_size));
    ui->cnt_steps_lineEdit_4->setText(QString::number(draw_time_params->cnt_steps));

    ui->buttonBox->disconnect();
    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &DrawTimeDialog::on_buttonBox_accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            this, &DrawTimeDialog::on_buttonBox_rejected);
}


double DrawTimeDialog::get_lambda_min() const{
    return ui->lambda_min_lineEdit->text().toDouble();
}

double DrawTimeDialog::get_lambda_max() const{
    return ui->lambda_max_lineEdit_2->text().toDouble();
}

int DrawTimeDialog::get_sample_size() const{
    return ui->sample_size_lineEdit_3->text().toInt();
}

int DrawTimeDialog::get_cnt_steps() const{
    return ui->cnt_steps_lineEdit_4->text().toInt();
}

void DrawTimeDialog::on_buttonBox_rejected(){
    reject();
}




void DrawTimeDialog::on_buttonBox_accepted(){
    int res = 0;

    res += check_dbl_field(0.5, 50, QString("lambda_min"), ui->lambda_min_lineEdit->text());
    res += check_dbl_field(0.5, 50, QString("lambda_max"), ui->lambda_max_lineEdit_2->text());
    res += check_int_field(1000, 200000, QString("sample_size"), ui->sample_size_lineEdit_3->text());
    res += check_int_field(10, 20, QString("cnt_steps"), ui->cnt_steps_lineEdit_4->text());

    if(res != 0){
        return;
    }

    if(ui->lambda_min_lineEdit->text().toInt() > ui->lambda_max_lineEdit_2->text().toInt()){
        QMessageBox::warning(nullptr, "Ошибка", QString("lambda_min >= lambda_max"));
        return;
    }

    accept();
}


DrawTimeDialog::~DrawTimeDialog()
{
    delete ui;
}
