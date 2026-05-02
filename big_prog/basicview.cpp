#include "basicview.h"
#include <QDebug>
#include <iostream>
#include <limits>





BasicView::BasicView(QWidget *parent, Document* doc)
    : QWidget{parent}, index(0),  _doc(doc),
      hist_params(new HistDrawParams), pdist_draw_params(new PDistDrawParams)
{}

void BasicView::set_index(int i){
    index = i;
}

void BasicView::set_doc(Document* doc){
    _doc = doc;
}


void BasicView::draw_hist_event(QPainter& painter){
    int w = this->size().width();
    int h = this->size().height();

    int N = _doc -> hist_gen_params -> sample -> get_sample_size();
    int range = _doc -> hist_gen_params -> sample -> get_range();
    int min_val = _doc -> hist_gen_params -> sample -> get_min_val();
    int max_val = _doc -> hist_gen_params -> sample -> get_max_val();
    double* freq = _doc -> hist_gen_params -> sample -> get_freq();

    int margin = h/10;


    // draw frame
    painter.setBrush(hist_params->_bg_clr);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(margin, margin, w - 2 * margin, h - 2 * margin);


    // draw title
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", margin/(3), QFont::Bold));
    QString title = QString("Гистограмма (sample_size = %1, min = %2, max = %3)")
                    .arg(N)
                    .arg(min_val)
                    .arg(max_val);
    painter.drawText(4, 0, w, margin, Qt::AlignCenter, title);


    // draw axes
    painter.setPen(QPen(Qt::black, 3));
    painter.drawLine(margin, h - margin, margin, 0);
    painter.drawLine(margin, h - margin, w, h-margin);


    // some calculations
    int n_bins = std::min(hist_params->_n_bins, range);
    int plot_h = h - 2 * margin;
    int bin_width = (w - 2.0 * margin) / n_bins;
    /*
    range = cnt_adj_bins * (bin_range + 1) + cnt_norm_bins * (bin_range)
    */
    int bin_range = range / n_bins;
    // int cnt_norm_bins = n_bins - range % n_bins;
    int cnt_adj_bins = range % n_bins;


    // compute total_prob for each bin
    double* bin_probs = new double[n_bins]{};
    double* lower_bounds = new double[n_bins]{};
    int lower_b;
    int upper_b;
    int offset = cnt_adj_bins * (bin_range + 1);
    for(int i = 0; i < n_bins; ++i){

        if(i < cnt_adj_bins){
            lower_b = i * (bin_range + 1);
            upper_b = (i + 1) * (bin_range + 1);
            for(int j=lower_b; j<upper_b; ++j)
                bin_probs[i] += freq[j];
        }
        else{
            lower_b = offset + (i - cnt_adj_bins    ) * bin_range;
            upper_b = offset + (i - cnt_adj_bins + 1) * bin_range;
            for(int j=lower_b; j<upper_b; ++j)
                bin_probs[i] += freq[j];
        }
        lower_bounds[i] = lower_b + min_val;
    }

//        qDebug() << "probs:\n";
//        for(int i=0; i<n_bins; ++i){
//            qDebug() << bin_probs[i] << "\n";
//        }

    // compute max_prob
    double max_prob = -1;
    for(int i=0; i<n_bins; ++i){
        if(bin_probs[i]>=max_prob) max_prob = bin_probs[i];
    }


    // draw rects
    painter.setBrush(hist_params->_bin_clr);
    painter.setPen(QPen(hist_params->_border_clr, 3));

    painter.setFont(QFont("Arial", margin/3, QFont::Bold));
    for(int i = 0; i < n_bins; ++i){

        int bin_h = (bin_probs[i] / max_prob) * plot_h * 0.9;

        painter.drawRect(3 + margin + i * bin_width,
                         margin + plot_h - bin_h,
                         bin_width-bin_width/10,
                         bin_h);

        // draw X-ticks
        painter.drawText(3 + margin + i * bin_width, h-margin,
                         bin_width, margin,
                         Qt::AlignCenter,
                         QString::number(lower_bounds[i]));
    }


    // draw Y-ticks
    painter.setFont(QFont("Arial", margin/6, QFont::Bold));
    painter.setPen(QPen(Qt::black, 2));
    for(int i=0; i<11; ++i){
        painter.drawLine(3*(margin/4), margin + plot_h - i*plot_h/11,
                         margin, margin + plot_h - i*plot_h/11);

        painter.drawText(0, margin + plot_h - plot_h/22 - i*plot_h/11,
                         margin/2, plot_h/11,
                         Qt::AlignCenter,
                         QString::number(max_prob * (i/10.0), 'f', 2 ));
    }

    delete[] lower_bounds;
    delete[] bin_probs;
}

void BasicView::draw_pval_dist_event(QPainter& painter){
    int N = _doc->pdist_gen_params->N;

    double* F0 = _doc->pdist_gen_params->h0_sample;
    double* F1 = _doc->pdist_gen_params->h1_sample;

    int w = this->size().width();
    int h = this->size().height();

    int margin = h/10;
    int plot_h = h - 2 * margin;
    double step = (w - 2 * margin) / N;

    // draw frame
    painter.setBrush(QColor(245, 235, 240, 140));
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(margin, margin, w - 2 * margin, h - 2 * margin);


    // draw title
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", margin/(3), QFont::Bold));
    QString title = QString("Распределение pval");
    painter.drawText(4, 0, w, margin, Qt::AlignCenter, title);

    // draw axes
    painter.setPen(QPen(Qt::black, 3));
    painter.drawLine(margin, h - margin, margin, 0);
    painter.drawLine(margin, h - margin, w, h-margin);

    QColor legend_bg_clr = Qt::white;

    QColor h0_clr = pdist_draw_params->_h0_clr;
    int h0_lw = 4;

    QColor h1_clr = pdist_draw_params->_h1_clr;
    int h1_lw = 4;

    QColor uni_clr = pdist_draw_params->_uni_clr;
    int uni_lw = 2;

    // legend params
    int p1 = 6;
    double p2 = 0.7;
    painter.setBrush(legend_bg_clr);
    int leg_x = margin + step * (N-p1);
    int leg_y = margin + plot_h * p2;
    int leg_w = step * p1;
    int leg_h = plot_h * (1-p2);
    int leg_mrg = leg_w/10;
    painter.drawRect(leg_x,leg_y,leg_w,leg_h);

    painter.setFont(QFont("Arial", margin/6, QFont::Bold));


    // draw h0_pval_dist
    painter.setPen(QPen(h0_clr, h0_lw));

    // legend
    painter.drawLine(leg_x + leg_mrg, leg_y + leg_mrg + 1*(leg_h-2*leg_mrg)/6,
                     leg_x + leg_w / 2.0 , leg_y + leg_mrg + 1*(leg_h-2*leg_mrg)/6);


    painter.drawText(leg_x + leg_w / 2.0, leg_y + leg_mrg + 0*(leg_h-2*leg_mrg)/3,
                     leg_w / 2.0, (leg_h-2*leg_mrg)/3,
                     Qt::AlignCenter,
                     QString("H0_pval_ECDF"));

    // plot
    painter.drawLine(margin + step * 0, margin + plot_h,
                     margin + step * 1, margin + plot_h - plot_h * F0[0] * 10.0/11);
    for(int i=0; i<N-1; ++i){
        painter.drawLine(margin + step * (i+1), margin + plot_h - plot_h * F0[i] * 10.0/11,
                         margin + step * (i+2), margin + plot_h - plot_h * F0[i+1] * 10.0/11);
    }


    // draw h1_pval_dist
    painter.setPen(QPen(h1_clr, h1_lw));

    // legend
    painter.drawLine(leg_x + leg_mrg, leg_y + leg_mrg + 3*(leg_h-2*leg_mrg)/6,
                     leg_x + leg_w / 2.0 , leg_y + leg_mrg + 3*(leg_h-2*leg_mrg)/6);

    painter.drawText(leg_x + leg_w / 2.0, leg_y + leg_mrg + 1*(leg_h-2*leg_mrg)/3,
                     leg_w / 2.0, (leg_h-2*leg_mrg)/3,
                     Qt::AlignCenter,
                     QString("H1_pval_ECDF"));
    // plot

    painter.drawLine(margin + step * 0, margin + plot_h,
                     margin + step * 1, margin + plot_h - plot_h * F1[0] * 10.0/11);
    for(int i=0; i<N-1; ++i){
        painter.drawLine(margin + step * (i+1), margin + plot_h - plot_h * F1[i] * 10.0/11,
                         margin + step * (i+2), margin + plot_h - plot_h * F1[i+1] * 10.0/11);
    }

    // draw uni_dist
    painter.setPen(QPen(uni_clr, uni_lw));

    // legend
    painter.drawLine(leg_x + leg_mrg, leg_y + leg_mrg + 5*(leg_h-2*leg_mrg)/6,
                     leg_x + leg_w / 2.0 , leg_y + leg_mrg + 5*(leg_h-2*leg_mrg)/6);
    painter.drawText(leg_x + leg_w / 2.0, leg_y + leg_mrg + 2*(leg_h-2*leg_mrg)/3,
                     leg_w / 2.0, (leg_h-2*leg_mrg)/3,
                     Qt::AlignCenter,
                     QString("U[0,1]_CDF"));

    // plot
    for(int i=0; i<N; ++i){
        painter.drawLine(margin + step * i,
                         margin + plot_h - plot_h * i*1.0/N * 10.0/11,
                         margin + step * (i+1),
                         margin + plot_h - plot_h * (i+1)*1.0/N * 10.0/11);
    }


    // draw X-ticks
    painter.setFont(QFont("Arial", margin/6, QFont::Bold));
    painter.setPen(QPen(Qt::black, 2));
    for(int i=0; i<=N; ++i){
        painter.drawLine(margin + step * i, h - margin,
                         margin + step * i, h - 3*(margin/4));

        painter.save();
        painter.translate(margin/2 + step * i, h-margin/3);
        painter.rotate(-45);
        painter.drawText(0,0,
                         step, margin/2,
                         Qt::AlignCenter,
                         QString::number(i*1.0/N, 'f', 2 ));
        painter.restore();
    }

    // draw Y-ticks
    for(int i=0; i<11; ++i){
        painter.drawLine(3*(margin/4), margin + plot_h - i*plot_h/11,
                         margin, margin + plot_h - i*plot_h/11);

        painter.drawText(0, margin + plot_h - plot_h/22 - i*plot_h/11,
                         margin/2, plot_h/11,
                         Qt::AlignCenter,
                         QString::number(i/10.0, 'f', 2 ));
    }

}




void BasicView::draw_time_event(QPainter &painter){
    int cnt_steps = _doc->draw_time_params->cnt_steps;
    double lambda_min =  _doc->draw_time_params->lambda_min;
    double lambda_max =  _doc->draw_time_params->lambda_max;
    std::chrono::milliseconds* dur1 = _doc->draw_time_params->dur1;
    std::chrono::milliseconds* dur2 = _doc->draw_time_params->dur2;

    for(int i=0; i<=cnt_steps; ++i){
        qDebug() << "lambda = " << lambda_min + (i / cnt_steps) * (lambda_max - lambda_min) << ""  << dur1[i].count() << " " << dur2[i].count() << "\n";
    }
    qDebug() << "\n\n";

    int w = this->size().width();
    int h = this->size().height();

    int margin = h/10;
    int plot_h = h - 2 * margin;
    int N = cnt_steps + 1;
    double* F0 = new double[N];
    double* F1 = new double[N];
    double mn=std::numeric_limits<double>::max();
    double mx=-1;
    for(int i=0; i<N; ++i){
        F0[i] = _doc->draw_time_params->dur1[i].count();
        F1[i] = _doc->draw_time_params->dur2[i].count();
        mx = std::max(mx,F0[i]);
        mx = std::max(mx,F1[i]);
    }
    for(int i=0; i<N; ++i){
       F0[i] /= mx;
       F1[i] /= mx;
    }

    double step = (w - 2 * margin) / N;

    // draw frame
    painter.setBrush(QColor(245, 235, 240, 140));
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(margin, margin, w - 2 * margin, h - 2 * margin);


    // draw title
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", margin/(3), QFont::Bold));
    QString title = QString("Время моделирования (млсек) VS lambda [n=%1]").arg(_doc->draw_time_params->sample_size);
    painter.drawText(4, 0, w, margin, Qt::AlignCenter, title);

    // draw axes
    painter.setPen(QPen(Qt::black, 3));
    painter.drawLine(margin, h - margin, margin, 0);
    painter.drawLine(margin, h - margin, w, h-margin);

//    QColor legend_bg_clr = Qt::white;

    QColor h0_clr = Qt::red;
    int h0_lw = 4;

    QColor h1_clr = Qt::blue;
    int h1_lw = 4;

    // legend params
//    int p1 = 6;
//    double p2 = 0.7;
//    painter.setBrush(legend_bg_clr);
//    int leg_x = margin + step * (N-p1);
//    int leg_y = margin + plot_h * p2;
//    int leg_w = step * p1;
//    int leg_h = plot_h * (1-p2);
//    int leg_mrg = leg_w/10;
//    painter.drawRect(leg_x,leg_y,leg_w,leg_h);

    painter.setFont(QFont("Arial", margin/6, QFont::Bold));


    // draw h0_pval_dist
    painter.setPen(QPen(h0_clr, h0_lw));

    // legend
//    painter.drawLine(leg_x + leg_mrg, leg_y + leg_mrg + 1*(leg_h-2*leg_mrg)/6,
//                     leg_x + leg_w / 2.0 , leg_y + leg_mrg + 1*(leg_h-2*leg_mrg)/6);


//    painter.drawText(leg_x + leg_w / 2.0, leg_y + leg_mrg + 0*(leg_h-2*leg_mrg)/3,
//                     leg_w / 2.0, (leg_h-2*leg_mrg)/3,
//                     Qt::AlignCenter,
//                     QString("method_1"));

    // plot
    for(int i=0; i<N-1; ++i){
        painter.drawLine(margin + step * (i), margin + plot_h - plot_h * F0[i] * 10.0/11,
                         margin + step * (i+1), margin + plot_h - plot_h * F0[i+1] * 10.0/11);
    }


    // draw h1_pval_dist
    painter.setPen(QPen(h1_clr, h1_lw));

    // legend
//    painter.drawLine(leg_x + leg_mrg, leg_y + leg_mrg + 3*(leg_h-2*leg_mrg)/6,
//                     leg_x + leg_w / 2.0 , leg_y + leg_mrg + 3*(leg_h-2*leg_mrg)/6);

//    painter.drawText(leg_x + leg_w / 2.0, leg_y + leg_mrg + 1*(leg_h-2*leg_mrg)/3,
//                     leg_w / 2.0, (leg_h-2*leg_mrg)/3,
//                     Qt::AlignCenter,
//                     QString("method_2"));

    // plot
    for(int i=0; i<N-1; ++i){
        painter.drawLine(margin + step * (i), margin + plot_h - plot_h * F1[i] * 10.0/11,
                         margin + step * (i+1), margin + plot_h - plot_h * F1[i+1] * 10.0/11);
    }


    // draw X-ticks
    painter.setFont(QFont("Arial", margin/6, QFont::Bold));
    painter.setPen(QPen(Qt::black, 2));
    for(int i=0; i<N; ++i){
        painter.drawLine(margin + step * i, h - margin,
                         margin + step * i, h - 3*(margin/4));

        painter.save();
        painter.translate(margin/2 + step * i, h-margin/5);
        painter.rotate(-45);
        painter.drawText(0,0,
                         step, margin/2,
                         Qt::AlignCenter,
                         QString::number(lambda_min + ((double)i / cnt_steps) * (lambda_max - lambda_min), 'f', 2 ));
        painter.restore();
    }

    // draw Y-ticks
    for(int i=0; i<11; ++i){
        painter.drawLine(3*(margin/4), margin + plot_h - i*plot_h/11,
                         margin, margin + plot_h - i*plot_h/11);

        painter.drawText(0, margin + plot_h - plot_h/22 - i*plot_h/11,
                         margin/2, plot_h/11,
                         Qt::AlignCenter,
                         QString::number(i/10.0 * mx, 'f', 1 ));
    }


    delete[] F0;
    delete[] F1;

}

int BasicView::get_index() const{
    return index;
}

void BasicView::paintEvent(QPaintEvent *){
    QPainter painter(this);

    if(index==0){

    }

    if(index==1){
        draw_hist_event(painter);
    }

    if(index==2){
        draw_pval_dist_event(painter);
    }

    if(index==3){
        draw_time_event(painter);
    }

};

void BasicView::showEvent(QShowEvent *)
{
    int w = this->parentWidget()->size().width();
    int h = this->parentWidget()->size().height();
    setGeometry((int)(0.1*w), (int)(0.1*h), (int)(0.8*w), (int)(0.8*h));
}



BasicView::~BasicView(){
    delete hist_params;
    delete pdist_draw_params;
};







