#include "SetPDistDrawParamsDialog.h"
#include "ui_SetPDistDrawParamsDialog.h"

SetPDistDrawParamsDialog::SetPDistDrawParamsDialog(QWidget *parent,
                                                   PDistDrawParams* pdist_draw_params) :
    QDialog(parent),
    ui(new Ui::SetPDistDrawParamsDialog),
    _pdist_draw_params(new PDistDrawParams)
{
    _pdist_draw_params->_h0_clr = pdist_draw_params->_h0_clr;
    _pdist_draw_params->_h1_clr = pdist_draw_params->_h1_clr;
    _pdist_draw_params->_uni_clr = pdist_draw_params->_uni_clr;

    ui->setupUi(this);

    connect(ui->h0_pushButton, &QPushButton::clicked, this,
            &SetPDistDrawParamsDialog::on_h0_clr);
    connect(ui->h1_pushButton, &QPushButton::clicked, this,
            &SetPDistDrawParamsDialog::on_h1_clr);
    connect(ui->uni_pushButton, &QPushButton::clicked, this,
            &SetPDistDrawParamsDialog::on_uni_clr);
}

void SetPDistDrawParamsDialog::on_h0_clr(){
    QColor selectedColor = QColorDialog::getColor(_pdist_draw_params->_h0_clr, this, "Выберите цвет");
    if(selectedColor.isValid()){
        _pdist_draw_params->_h0_clr = selectedColor;
        update();
    }
}

void SetPDistDrawParamsDialog::on_h1_clr(){
    QColor selectedColor = QColorDialog::getColor(_pdist_draw_params->_h1_clr, this, "Выберите цвет");
    if(selectedColor.isValid()){
        _pdist_draw_params->_h1_clr = selectedColor;
        update();
    }
}

void SetPDistDrawParamsDialog::on_uni_clr(){
    QColor selectedColor = QColorDialog::getColor(_pdist_draw_params->_uni_clr, this, "Выберите цвет");
    if(selectedColor.isValid()){
        _pdist_draw_params->_uni_clr = selectedColor;
        update();
    }
}

void SetPDistDrawParamsDialog::paintEvent(QPaintEvent *){
    QPainter painter(this);

    int x = ui->h0_pushButton->geometry().x();
    int y = ui->h0_pushButton->geometry().y();
    int w = ui->h0_pushButton->geometry().width();
    int h = ui->h0_pushButton->geometry().height();

    painter.setBrush(_pdist_draw_params->_h0_clr);
    painter.drawRect(x + w + 10, y, w, h);

    y = ui->h1_pushButton->geometry().y();
    painter.setBrush(_pdist_draw_params->_h1_clr);
    painter.drawRect(x + w + 10, y, w, h);

    y = ui->uni_pushButton->geometry().y();
    painter.setBrush(_pdist_draw_params->_uni_clr);
    painter.drawRect(x + w + 10, y, w, h);
}


SetPDistDrawParamsDialog::~SetPDistDrawParamsDialog()
{
    delete ui;
}
