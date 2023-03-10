#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>
#include <QMouseEvent>

class ChartView : public QChartView {
public:
    ChartView(QChart* chart, QWidget* parent = nullptr) : QChartView(chart, parent) {}

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            startPos = event->pos();
        }
        QChartView::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        if (event->buttons() & Qt::LeftButton) {
            // Calculate the distance of the pan and update the chart view
            QPointF diff = event->pos() - startPos;
            chart()->scroll(-diff.x(), diff.y());
            startPos = QPointF(event->pos());
        }
        QChartView::mouseMoveEvent(event);
    }

private:
    QPointF startPos;
};

#endif // CHARTVIEW_H
