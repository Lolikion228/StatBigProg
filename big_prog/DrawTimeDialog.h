#ifndef DRAWTIMEDIALOG_H
#define DRAWTIMEDIALOG_H

#include <QDialog>
#include "DrawTimeParams.h"
#include "utils.h"

namespace Ui {
class DrawTimeDialog;
}

class DrawTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DrawTimeDialog(QWidget *parent = nullptr, DrawTimeParams* draw_time_params=nullptr);
    double get_lambda_min() const;
    double get_lambda_max() const;
    int get_sample_size() const;
    int get_cnt_steps() const;

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    ~DrawTimeDialog();

private:
    Ui::DrawTimeDialog *ui;
};

#endif // DRAWTIMEDIALOG_H
