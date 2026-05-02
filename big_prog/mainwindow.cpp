#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SetHistDrawParamsDialog.h"
#include <chrono>
#include "poisgen2.h"


const int SUPER_SEED = 2027;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    stdgen = new std::mt19937_64(SUPER_SEED);
    doc = new Document(stdgen);

    basic_view = new BasicView(this, doc);
    basic_view->set_index(1);
    basic_view->update();
    basic_view->show();

    ui->setupUi(this);

    connect(ui->actionSetHistGenParams, &QAction::triggered, this, &MainWindow::onSetHistGenParamsDialog);
    connect(ui->actionResetHistParams, &QAction::triggered, this, &MainWindow::onResetHistParams);
    connect(ui->actionDrawHist, &QAction::triggered, this, &MainWindow::onDrawHist);
    connect(ui->GenSampleButton, &QPushButton::clicked, this, &MainWindow::onGenSampleButton);

    connect(ui->actionSetPDistGenParams, &QAction::triggered, this, &MainWindow::onSetPDistGenParamsDialog);
    connect(ui->actionResetPDistParams,  &QAction::triggered, this, &MainWindow::onResetPDistParams);
    connect(ui->actionDrawPDist, &QAction::triggered, this, &MainWindow::onDrawPDist);

    connect(ui->actionDrawTime, &QAction::triggered, this, &MainWindow::onDrawTime);

    connect(ui->actionClearAll, &QAction::triggered, this,  [this](){
        basic_view->set_index(0);
        basic_view->hide();
    });
}


void MainWindow::onSetPDistGenParamsDialog(){
    SetPDistGenParamsDialog dialog(doc, this);
    int res = dialog.exec();
    if(res == QDialog::Accepted){
        doc->pdist_gen_params->h0_lambda = dialog.get_h0_lambda();
        doc->pdist_gen_params->h1_lambda = dialog.get_h1_lambda();
        doc->pdist_gen_params->main_sample_size = dialog.get_main_sample_size();
        doc->pdist_gen_params->psample_size = dialog.get_psample_size();
        int ix = dialog.get_method_ix();
        doc->pdist_gen_params->method_ix = ix;
        if(ix == 1){
            doc->pdist_gen_params->h0_gen = new PoisGen1(doc->pdist_gen_params->h0_lambda, stdgen);
            doc->pdist_gen_params->h1_gen = new PoisGen1(doc->pdist_gen_params->h1_lambda, stdgen);
        }
        if(ix == 2){
            doc->pdist_gen_params->h0_gen = new PoisGen2(doc->pdist_gen_params->h0_lambda, stdgen);
            doc->pdist_gen_params->h1_gen = new PoisGen2(doc->pdist_gen_params->h1_lambda, stdgen);
        }

        delete[] doc->pdist_gen_params->h0_sample;
        delete[] doc->pdist_gen_params->h1_sample;

        doc -> pdist_gen_params -> N = get_pdist(doc->pdist_gen_params -> h0_gen,
                                                 doc->pdist_gen_params -> h1_gen,
                                                 doc->pdist_gen_params -> psample_size,
                                                 doc->pdist_gen_params -> main_sample_size,
                                                 doc->pdist_gen_params -> h0_sample,
                                                 doc->pdist_gen_params -> h1_sample);

        basic_view->set_index(2);
        basic_view->update();
        basic_view->show();
    }
}

void MainWindow::onResetPDistParams(){
    delete doc->pdist_gen_params;
    delete basic_view->pdist_draw_params;

    doc->pdist_gen_params = new PDistGenParams(stdgen);
    basic_view->pdist_draw_params = new PDistDrawParams;

    basic_view->set_index(2);
    basic_view->update();
    basic_view->show();
}

void MainWindow::onDrawPDist(){
    SetPDistDrawParamsDialog dialog(this, this->basic_view->pdist_draw_params);
    int res = dialog.exec();
    if(res == QDialog::Accepted){
        basic_view->pdist_draw_params->_h0_clr = dialog._pdist_draw_params->_h0_clr;
        basic_view->pdist_draw_params->_h1_clr = dialog._pdist_draw_params->_h1_clr;
        basic_view->pdist_draw_params->_uni_clr = dialog._pdist_draw_params->_uni_clr;
        basic_view->set_index(2);
        basic_view->update();
        basic_view->show();
    }
}


void MainWindow::onResetHistParams(){
    delete basic_view->hist_params;
    delete doc->hist_gen_params;

    doc->hist_gen_params = new HistGenParams(stdgen);
    basic_view->hist_params = new HistDrawParams;

    basic_view->set_index(1);
    basic_view->update();
    basic_view->show();
}

void MainWindow::onSetHistGenParamsDialog(){
    SetHistGenParamsDialog dialog(doc, this);
    int res = dialog.exec();

    if(res == QDialog::Accepted){
        doc->hist_gen_params->h1_lambda = dialog.get_h1_lambda();
        doc->hist_gen_params->method_ix = dialog.get_method_ix();

        int N = dialog.get_sample_size();

        if(dialog.get_method_ix()==1){
            delete doc->hist_gen_params->curr_gen;
            doc->hist_gen_params->curr_gen = new PoisGen1(doc->hist_gen_params->h1_lambda, stdgen);
        }
        if(dialog.get_method_ix()==2){
            delete doc->hist_gen_params->curr_gen;
            doc->hist_gen_params->curr_gen = new PoisGen2(doc->hist_gen_params->h1_lambda, stdgen);
        }

        int* sample = new int[N];
        get_sample(N, sample, doc->hist_gen_params->curr_gen);
        doc->hist_gen_params->sample->set_sample(sample,N);

        basic_view->set_index(1);
        basic_view->update();
        basic_view->show();
    }

}

void MainWindow::onDrawHist(){
    SetHistDrawParamsDialog dialog(this, basic_view->hist_params);
    int res = dialog.exec();
    if(res == QDialog::Accepted){
        basic_view->hist_params->_n_bins = dialog._hist_draw_params->_n_bins;
        basic_view->hist_params->_bg_clr = dialog._hist_draw_params->_bg_clr;
        basic_view->hist_params->_bin_clr = dialog._hist_draw_params->_bin_clr;
        basic_view->hist_params->_border_clr = dialog._hist_draw_params->_border_clr;
        basic_view->set_index(1);
        basic_view->update();
        basic_view->show();
    }
}


void MainWindow::onGenSampleButton(){

    int ix = basic_view->get_index();

    if(ix == 0){
        basic_view->set_index(1);
    }
    if(ix == 1){
        int N = doc->hist_gen_params->sample->get_sample_size();
        int* sample = new int[N];
        get_sample(N, sample, doc->hist_gen_params->curr_gen);
        doc->hist_gen_params->sample->set_sample(sample,N);
    }
    if(ix == 2){
        doc->pdist_gen_params->N = get_pdist(doc->pdist_gen_params->h0_gen,
                                             doc->pdist_gen_params->h1_gen,
                                             doc->pdist_gen_params->psample_size,
                                             doc->pdist_gen_params->main_sample_size,
                                             doc->pdist_gen_params->h0_sample,
                                             doc->pdist_gen_params->h1_sample);
    }
    if(ix == 3){

    }

    basic_view->update();
    basic_view->show();
};


void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    int w = event->size().width();
    int h = event->size().height();
    this->basic_view->setGeometry((int)(0.1*w), (int)(0.1*h), (int)(0.8*w), (int)(0.8*h));
    this->ui->GenSampleButton->setGeometry((int)(0.1*w) + (int)(0.8*w*(1.0/3)),1, (int)(0.8*w*(1.0/3)), (int)(0.05*h));
}



void MainWindow::onDrawTime(){
    DrawTimeDialog dialog(this, doc->draw_time_params);
    int res = dialog.exec();
    if(res==QDialog::Accepted){
        doc->draw_time_params->lambda_min = dialog.get_lambda_min();
        doc->draw_time_params->lambda_max = dialog.get_lambda_max();
        doc->draw_time_params->cnt_steps = dialog.get_cnt_steps();
        doc->draw_time_params->sample_size = dialog.get_sample_size();

        basic_view->set_index(3);
        basic_view->update();
        basic_view->show();
    }

}

void MainWindow::onResetTimeParams(){

}

MainWindow::~MainWindow()
{
    delete basic_view;
    delete doc;
    delete ui;
    delete stdgen;
}

