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
    basic_view->set_what2draw(DrawObj::Hist);
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
    connect(ui->actionResetTimeParams, &QAction::triggered, this, &MainWindow::onResetTimeParams);

    connect(ui->actionClearAll, &QAction::triggered, this,  [this](){
        basic_view->set_what2draw(DrawObj::None);
        basic_view->hide();
    });
}


void MainWindow::onSetPDistGenParamsDialog(){
    SetPDistGenParamsDialog dialog(doc, this);
    int res = dialog.exec();
    if(res == QDialog::Accepted){
        doc->pdist_gen_params->main_sample_size = dialog.get_main_sample_size();
        doc->pdist_gen_params->psample_size = dialog.get_psample_size();
        doc->pdist_gen_params->sgnf_level = dialog.get_sgnfc_level();

        doc->
        pdist_gen_params->
        set_params(dialog.get_method_ix(),
                   dialog.get_h0_lambda(),
                   dialog.get_h1_lambda());

        delete[] doc->pdist_gen_params->h0_sample;
        delete[] doc->pdist_gen_params->h1_sample;
        int N = doc->pdist_gen_params->N;
        doc->pdist_gen_params->h0_sample = new double[N]{};
        doc->pdist_gen_params->h1_sample = new double[N]{};
        doc -> pdist_gen_params -> N = get_pdist(doc->pdist_gen_params -> h0_sample,
                                                 doc->pdist_gen_params -> h1_sample,
                                                 doc->pdist_gen_params -> h0_gen,
                                                 doc->pdist_gen_params -> h1_gen,
                                                 doc->pdist_gen_params -> psample_size,
                                                 doc->pdist_gen_params -> main_sample_size,
                                                 doc->pdist_gen_params -> sgnf_level,
                                                 doc->pdist_gen_params -> obs_sgnf_level,
                                                 doc->pdist_gen_params -> obs_power);

        basic_view->set_what2draw(DrawObj::PvalDist);
        basic_view->update();
        basic_view->show();
    }
}

void MainWindow::onResetPDistParams(){
    delete doc->pdist_gen_params;
    delete basic_view->pdist_draw_params;

    doc->pdist_gen_params = new PDistGenParams(stdgen);
    basic_view->pdist_draw_params = new PDistDrawParams;

    basic_view->set_what2draw(DrawObj::PvalDist);
    basic_view->update();
    basic_view->show();
}

void MainWindow::onDrawPDist(){
    SetPDistDrawParamsDialog dialog(*(basic_view->pdist_draw_params), this);
    int res = dialog.exec();
    if(res == QDialog::Accepted){
        basic_view->pdist_draw_params->_h0_clr = dialog._pdist_draw_params._h0_clr;
        basic_view->pdist_draw_params->_h1_clr = dialog._pdist_draw_params._h1_clr;
        basic_view->pdist_draw_params->_uni_clr = dialog._pdist_draw_params._uni_clr;
        basic_view->set_what2draw(DrawObj::PvalDist);
        basic_view->update();
        basic_view->show();
    }
}


void MainWindow::onResetHistParams(){
    delete basic_view->hist_params;
    delete doc->hist_gen_params;

    doc->hist_gen_params = new HistGenParams(stdgen);
    basic_view->hist_params = new HistDrawParams;

    basic_view->set_what2draw(DrawObj::Hist);
    basic_view->update();
    basic_view->show();
}

void MainWindow::onSetHistGenParamsDialog(){
    SetHistGenParamsDialog dialog(doc, this);
    int res = dialog.exec();

    if(res == QDialog::Accepted){
        doc->
        hist_gen_params->
        set_params(dialog.get_h1_lambda(),
                    dialog.get_method_ix());

        int N = dialog.get_sample_size();
        doc->hist_gen_params->curr_gen->gen_sample(N);

        basic_view->set_what2draw(DrawObj::Hist);
        basic_view->update();
        basic_view->show();
    }

}

void MainWindow::onDrawHist(){
    SetHistDrawParamsDialog dialog(*(basic_view->hist_params), this);
    int res = dialog.exec();
    if(res == QDialog::Accepted){
        basic_view->hist_params->_bg_clr = dialog._hist_draw_params._bg_clr;
        basic_view->hist_params->_bin_clr = dialog._hist_draw_params._bin_clr;
        basic_view->hist_params->_border_clr = dialog._hist_draw_params._border_clr;
        basic_view->set_what2draw(DrawObj::Hist);
        basic_view->update();
        basic_view->show();
    }
}


void MainWindow::onGenSampleButton(){

    switch(basic_view->get_what2draw()){

        case DrawObj::None: {
            basic_view->set_what2draw(DrawObj::Hist);
            break;
        }

        case DrawObj::Hist: {
            int N = doc->hist_gen_params->curr_gen->_sample_size;
            doc->hist_gen_params->curr_gen->gen_sample(N);
            break;
        }

        case DrawObj::PvalDist: {
            delete[] doc->pdist_gen_params->h0_sample;
            delete[] doc->pdist_gen_params->h1_sample;
            int N = doc->pdist_gen_params->N;
            doc->pdist_gen_params->h0_sample = new double[N]{};
            doc->pdist_gen_params->h1_sample = new double[N]{};
            doc->pdist_gen_params->N = get_pdist(doc->pdist_gen_params->h0_sample,
                                                 doc->pdist_gen_params->h1_sample,
                                                 doc->pdist_gen_params->h0_gen,
                                                 doc->pdist_gen_params->h1_gen,
                                                 doc->pdist_gen_params->psample_size,
                                                 doc->pdist_gen_params->main_sample_size,
                                                 doc->pdist_gen_params->sgnf_level,
                                                 doc->pdist_gen_params->obs_sgnf_level,
                                                 doc->pdist_gen_params->obs_power);
            break;
        }

        case DrawObj::TimeDep: {
            doc->draw_time_params->update_dur();
            break;
        }

        default: {}
    }

    basic_view->update();
    basic_view->show();
}


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
        doc->draw_time_params->update_dur();

        basic_view->set_what2draw(DrawObj::TimeDep);
        basic_view->update();
        basic_view->show();
    }

}

void MainWindow::onResetTimeParams(){
    delete doc->draw_time_params;
    doc->draw_time_params = new DrawTimeParams(stdgen);

    basic_view->set_what2draw(DrawObj::TimeDep);
    basic_view->update();
    basic_view->show();
}

MainWindow::~MainWindow()
{
    delete basic_view;
    delete doc;
    delete ui;
    delete stdgen;
}

