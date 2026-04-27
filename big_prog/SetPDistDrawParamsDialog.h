#ifndef SETPDISTDRAWPARAMSDIALOG_H
#define SETPDISTDRAWPARAMSDIALOG_H

#include <QDialog>

namespace Ui {
class SetPDistDrawParamsDialog;
}

class SetPDistDrawParamsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetPDistDrawParamsDialog(QWidget *parent = nullptr);
    ~SetPDistDrawParamsDialog();

private:
    Ui::SetPDistDrawParamsDialog *ui;
};

#endif // SETPDISTDRAWPARAMSDIALOG_H
