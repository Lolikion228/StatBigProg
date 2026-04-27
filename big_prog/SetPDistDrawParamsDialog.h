#ifndef SETPDISTDRAWPARAMSDIALOG_H
#define SETPDISTDRAWPARAMSDIALOG_H

#include <QDialog>
#include <QPainter>
#include "basicview.h"
#include <QColorDialog>

namespace Ui {
class SetPDistDrawParamsDialog;
}

class SetPDistDrawParamsDialog : public QDialog
{
    Q_OBJECT
protected:

public:
    PDistDrawParams* _pdist_draw_params;
    explicit SetPDistDrawParamsDialog(QWidget *parent = nullptr,
                                      PDistDrawParams* pdist_draw_params=nullptr);
    void paintEvent(QPaintEvent *) override;
    void on_h0_clr();
    void on_h1_clr();
    void on_uni_clr();
    ~SetPDistDrawParamsDialog();

private:
    Ui::SetPDistDrawParamsDialog *ui;
};

#endif // SETPDISTDRAWPARAMSDIALOG_H
