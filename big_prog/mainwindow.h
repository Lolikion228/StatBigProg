#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SetHistGenParamsDialog.h"
#include "SetHistGenParamsDialog.h"
#include "SetPDistGenParamsDialog.h"
#include "SetPDistDrawParamsDialog.h"
#include <QDebug>
#include "poisgen1.h"
#include "utils.h"
#include <QMessageBox>
#include "basicview.h"
#include <QResizeEvent>
#include "DrawTimeDialog.h"
#include "DrawTimeParams.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    Document* doc;
    BasicView* basic_view;
    std::mt19937_64* stdgen;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void onSetHistGenParamsDialog();
    void onResetHistParams();
    void onDrawHist();

    void onSetPDistGenParamsDialog();
    void onResetPDistParams();
    void onDrawPDist();

    void onGenSampleButton();


    void onDrawTime();
    void onResetTimeParams();

    void resizeEvent(QResizeEvent *event) override;
};
#endif // MAINWINDOW_H
