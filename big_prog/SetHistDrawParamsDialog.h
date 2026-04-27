#ifndef SETHISTDRAWPARAMSDIALOG_H
#define SETHISTDRAWPARAMSDIALOG_H

#include <QDialog>
#include "basicview.h"


namespace Ui {
class SetHistDrawParamsDialog;
}

class SetHistDrawParamsDialog : public QDialog
{
    Q_OBJECT
protected:

public:
    HistDrawParams* _hist_draw_params;
    explicit SetHistDrawParamsDialog(QWidget *parent = nullptr, HistDrawParams* hist_draw_params=nullptr);
    int get_n_bins() const;
    void paintEvent(QPaintEvent *) override;
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_bg_clr();
    void on_rect_clr();
    void on_border_clr();

    ~SetHistDrawParamsDialog();

private:
    Ui::SetHistDrawParamsDialog *ui;
};

#endif // SETHISTDRAWPARAMSDIALOG_H
