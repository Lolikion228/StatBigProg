#ifndef BASICVIEW_H
#define BASICVIEW_H

#include <QWidget>
#include <QPainter>
#include "document.h"
#include <cmath>


struct HistDrawParams{
    int _n_bins = 18;
    QColor _bg_clr = QColor(245, 235, 240, 140);
    QColor _bin_clr = QColor(210, 170, 185, 200);
    QColor _border_clr = QColor(180, 140, 155, 255);
};

struct PDistDrawParams{
    QColor _h0_clr = Qt::red;
    QColor _h1_clr = Qt::blue;
    QColor _uni_clr = Qt::green;
};



class BasicView : public QWidget
{
    Q_OBJECT

protected:
    int index;
    Document* _doc;

public:
    HistDrawParams* hist_params;
    PDistDrawParams* pdist_draw_params;
    explicit BasicView(QWidget *parent = nullptr, Document *doc=nullptr);
    void set_index(int ix);
    int get_index() const;
    void set_doc(Document* doc);
    void paintEvent(QPaintEvent *) override;
    void draw_hist_event(QPainter& painter);
    void draw_pval_dist_event(QPainter& painter);
    void showEvent(QShowEvent *) override;
signals:

};

#endif // BASICVIEW_H
