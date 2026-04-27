#include "sethistdrawparamsdialog.h"
#include "ui_sethistdrawparamsdialog.h"
#include <QMessageBox>
#include <QColorDialog>
#include <QPainter>

SetHistDrawParamsDialog::SetHistDrawParamsDialog(QWidget *parent, HistDrawParams* hist_draw_params) :
    QDialog(parent),
    ui(new Ui::SetHistDrawParamsDialog),
    _hist_draw_params(hist_draw_params)
{
    ui->setupUi(this);

    ui->n_bins_edit->setText(QString::number(_hist_draw_params->_n_bins));

    ui->buttonBox->disconnect();
    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &SetHistDrawParamsDialog::on_buttonBox_accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            this, &SetHistDrawParamsDialog::on_buttonBox_rejected);

    connect(ui->SetBgClrButton, &QPushButton::clicked, this, &SetHistDrawParamsDialog::on_bg_clr);
    connect(ui->SetRectClrButton, &QPushButton::clicked, this, &SetHistDrawParamsDialog::on_rect_clr);
    connect(ui->SetBorderClrButton, &QPushButton::clicked, this, &SetHistDrawParamsDialog::on_border_clr);




}

void SetHistDrawParamsDialog::paintEvent(QPaintEvent *){
    QPainter painter(this);

    int x = ui->SetBgClrButton->geometry().x();
    int y = ui->SetBgClrButton->geometry().y();
    int w = ui->SetBgClrButton->geometry().width();
    int h = ui->SetBgClrButton->geometry().height();

    painter.setBrush(_hist_draw_params->_bg_clr);
    painter.drawRect(x + w + 10, y, w, h);


    y = ui->SetRectClrButton->geometry().y();
    painter.setBrush(_hist_draw_params->_bin_clr);
    painter.drawRect(x + w + 10, y, w, h);

    y = ui->SetBorderClrButton->geometry().y();
    painter.setBrush(_hist_draw_params->_border_clr);
    painter.drawRect(x + w + 10, y, w, h);


}

void SetHistDrawParamsDialog::on_bg_clr(){
    QColor selectedColor = QColorDialog::getColor(_hist_draw_params->_bg_clr, this, "Выберите цвет");
    if(selectedColor.isValid()){
        _hist_draw_params->_bg_clr = selectedColor;
        update();
    }
}

void SetHistDrawParamsDialog::on_border_clr(){
    QColor selectedColor = QColorDialog::getColor(_hist_draw_params->_border_clr, this, "Выберите цвет");
    if(selectedColor.isValid()){
        _hist_draw_params->_border_clr = selectedColor;
        update();
    }
}

void SetHistDrawParamsDialog::on_rect_clr(){
    QColor selectedColor = QColorDialog::getColor(_hist_draw_params->_bin_clr, this, "Выберите цвет");
    if(selectedColor.isValid()){
        _hist_draw_params->_bin_clr = selectedColor;
        update();
    }
}



int SetHistDrawParamsDialog::get_n_bins() const{
    return this->ui->n_bins_edit->text().toInt();
};

void SetHistDrawParamsDialog::on_buttonBox_accepted()
{
    QString text = ui->n_bins_edit->text();
    int minValue = 2;
    int maxValue = 50;

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Вы ничего не ввели!");
        return;
    }

    bool ok;
    int number = text.toInt(&ok);

    if ( (!ok) || (number < minValue || number > maxValue) ) {
        QMessageBox::warning(this, "Ошибка",
                            QString("Нужно ввести целое число от %1 до %2!")
                            .arg(minValue).arg(maxValue));
        return;
    }

    accept();
}


void SetHistDrawParamsDialog::on_buttonBox_rejected()
{
    reject();
}

SetHistDrawParamsDialog::~SetHistDrawParamsDialog()
{
    delete ui;
}
