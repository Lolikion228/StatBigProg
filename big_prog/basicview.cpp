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



void draw_frame_and_axes(QPainter& painter, const QString& title, int w, int h, int margin,
                         QColor bg_color, QPen pen) {
    // draw frame
    painter.setBrush(bg_color);
    painter.setPen(pen);
    painter.drawRect(margin, margin, w - 2 * margin, h - 2 * margin);

    // draw title
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", margin / 3, QFont::Bold));
    painter.drawText(4, 0, w, margin, Qt::AlignCenter, title);

    // draw axes
    painter.setPen(QPen(Qt::black, 3));
    painter.drawLine(margin, h - margin, margin, 0);
    painter.drawLine(margin, h - margin, w, h - margin);
}

void draw_xticks(QPainter& painter, int y, double step, const double* values, int n_values, int margin) {
    if (n_values <= 0) return;

    painter.setFont(QFont("Arial", margin / 6, QFont::Bold));
    painter.setPen(QPen(Qt::black, 2));

    for (int i = 0; i < n_values; ++i) {
        double x_pos = margin + step * i;

        // draw tick line
        painter.drawLine(x_pos, y, x_pos, y + (margin / 4));

        // draw tick label
        painter.save();
        painter.translate(x_pos - margin / 2, y + 2 * margin / 3);
        painter.rotate(-45);
        painter.drawText(0, 0, step, margin / 2, Qt::AlignCenter,
                         QString::number(values[i], 'f', 2));
        painter.restore();
    }
}


void draw_yticks(QPainter& painter, int x, double y0, int n_ticks, double *vals, int h, int margin, int ndigits) {
    if (n_ticks <= 0) return;

    int plot_h = h - 2 * margin;

    painter.setFont(QFont("Arial", margin / 6, QFont::Bold));
    painter.setPen(QPen(Qt::black, 2));

    for (int i = 0; i < n_ticks; ++i) {
        double y_pos = y0 - i * plot_h / n_ticks;

        // draw tick line
        painter.drawLine(x, y_pos, x + margin / 4, y_pos);

        // draw tick label
        painter.drawText(0, y_pos - plot_h / 22, margin / 2, plot_h/11,
                         Qt::AlignCenter, QString::number(vals[i], 'f', ndigits));
    }
}

void draw_line_plot(QPainter& painter, const double* data, int N, const QColor& color, int line_width, int w, int h, int margin, double step) {
    if (N <= 1 || !data) return;

    int plot_h = h - 2 * margin;

    painter.setPen(QPen(color, line_width));


    // draw line segments
    for (int i = 0; i < N - 1; ++i) {
        double x1 = margin + step * i;
        double y1 = margin + plot_h - plot_h * (data[i]) * 10.0 / 11;
        double x2 = margin + step * (i + 1);
        double y2 = margin + plot_h - plot_h * (data[i + 1]) * 10.0 / 11;
        painter.drawLine(x1, y1, x2, y2);
    }
}


void draw_legend(int N, QPainter& painter, const QList<LegendItem>& items, int h, int margin, double step) {
    if (items.isEmpty()) return;

    int plot_h = h - 2 * margin;

    // legend parameters
    int p1 = 6;
    double p2 = 0.7;
    int leg_x = margin + step * (N - p1);
    int leg_y = margin + plot_h * p2;
    int leg_w = step * p1;
    int leg_h = plot_h * (1 - p2);
    int leg_mrg = leg_w / 10;

    painter.setBrush(Qt::white);
    painter.setPen(QPen(Qt::black,2));
    painter.drawRect(leg_x, leg_y, leg_w, leg_h);

    painter.setFont(QFont("Arial", margin / 6, QFont::Bold));

    int item_height = (leg_h - 2 * leg_mrg) / items.size();
    int y_offset = leg_mrg;

    for (int i = 0; i < items.size(); ++i) {
        const LegendItem& item = items[i];
        int y_center = leg_y + y_offset + item_height / 2;

        // draw line
        painter.setPen(QPen(item.color, item.line_width));
        painter.drawLine(leg_x + leg_mrg, y_center,
                         leg_x + leg_w / 2.0, y_center);

        // draw text
        painter.setPen(QPen(Qt::black, 1));
        painter.drawText(leg_x + leg_w / 2.0, leg_y + y_offset,
                         leg_w / 2.0, item_height,
                         Qt::AlignLeft | Qt::AlignVCenter,
                         item.label);

        y_offset += item_height;
    }
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

    QString title = QString("Гистограмма (sample_size = %1, min = %2, max = %3)")
                    .arg(N)
                    .arg(min_val)
                    .arg(max_val);
    draw_frame_and_axes(painter, title, w, h, margin, hist_params->_bg_clr, QPen(Qt::black, 2));

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


    double *vals = new double[11];
    for(int i=0; i<11; ++i){
        vals[i] = max_prob * (i/10.0);
    }
    draw_yticks(painter, 3*(margin/4),  margin + plot_h, 11, vals, h, margin, 2);


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

    QString title = QString("Распределение pval");
    draw_frame_and_axes(painter, title, w, h, margin, QColor(245, 235, 240, 140), QPen(Qt::black, 2));

    QColor h0_clr = pdist_draw_params->_h0_clr;
    int h0_lw = 4;

    QColor h1_clr = pdist_draw_params->_h1_clr;
    int h1_lw = 4;

    QColor uni_clr = pdist_draw_params->_uni_clr;
    int uni_lw = 2;

    // draw H0_dist
    double *vals = new double[N+1]{};
    for(int i=1; i<N+1; ++i){
        vals[i] = F0[i-1];
    }
    draw_line_plot(painter, vals, N+1, h0_clr, h0_lw, w, h, margin, step);


    //draw H1_dist
    vals = new double[N+1]{};
    for(int i=1; i<N+1; ++i){
        vals[i] = F1[i-1];
    }
    draw_line_plot(painter, vals, N+1, h1_clr, h1_lw, w, h, margin, step);


    // draw uni_dist
    painter.setPen(QPen(uni_clr, uni_lw));
    for(int i=0; i<N; ++i){
        painter.drawLine(margin + step * i,
                         margin + plot_h - plot_h * i*1.0/N * 10.0/11,
                         margin + step * (i+1),
                         margin + plot_h - plot_h * (i+1)*1.0/N * 10.0/11);
    }


    QList<LegendItem> lisp = {LegendItem{h0_clr, h0_lw, QString("H0_pval_ECDF"), 0},
                             LegendItem{h1_clr, h1_lw, QString("H1_pval_ECDF"), 1},
                             LegendItem{uni_clr, uni_lw, QString("H0_pval_ECDF"), 2}};
    draw_legend(N, painter, lisp, h, margin, step);


    vals = new double[N+1];
    for(int i=0; i<=N; ++i){
        vals[i] = i*1.0/N;
    }
    draw_xticks(painter, h - margin, step, vals, N+1, margin);


    for(int i=0; i<11; ++i){
        vals[i] = i/10.0;
    }
    draw_yticks(painter, 3*(margin/4),  margin + plot_h, 11, vals, h, margin, 2);
}


void BasicView::draw_time_event(QPainter &painter){
    int cnt_steps = _doc->draw_time_params->cnt_steps;
    double lambda_min =  _doc->draw_time_params->lambda_min;
    double lambda_max =  _doc->draw_time_params->lambda_max;

    int w = this->size().width();
    int h = this->size().height();
    int margin = h/10;
    int plot_h = h - 2 * margin;
    int N = cnt_steps + 1;
    double step = (w - 2 * margin) / N;

    double* F0 = new double[N];
    double* F1 = new double[N];
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


    QString title = QString("Время моделирования (млсек) VS lambda [n=%1]").arg(_doc->draw_time_params->sample_size);
    draw_frame_and_axes(painter, title, w, h, margin, QColor(245, 235, 240, 140), QPen(Qt::black, 2));


    draw_line_plot(painter, F0, N, Qt::red, 4, w, h, margin, step);
    draw_line_plot(painter, F1, N, Qt::blue, 4, w, h, margin, step);


    double *vals = new double[N];
    for(int i=0; i<N; ++i){
        vals[i] = lambda_min + ((double)i / cnt_steps) * (lambda_max - lambda_min);
    }
    draw_xticks(painter, h - margin, step, vals, N, margin);


    for(int i=0; i<11; ++i){
        vals[i] = i/10.0 * mx;
    }
    draw_yticks(painter, 3*(margin/4),  margin + plot_h, 11, vals, h, margin, 1);

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







