#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QFont>

#include "mychartwindow.h"

namespace myNamespace{
    extern float fin_ans,sec_ans,ok;

}

MyChartWindow::MyChartWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create the spline series and set its name
    QSplineSeries *series_bigOneChart = new QSplineSeries();
    series_bigOneChart->setName("Spline Values");

    // Create the chart and add the series to it
    QChart *chart_bigOneChart = new QChart();
    chart_bigOneChart->addSeries(series_bigOneChart);
    chart_bigOneChart->setTitle("Simple spline chart example");

    // Create the x and y axes and set their ranges
    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();
    axisX->setRange(0, 20);
    axisY->setRange(-7, 12);

    // Set the fonts and colors of the axes labels
    QFont labelsFont;
    labelsFont.setPixelSize(12);
    axisX->setLabelsFont(labelsFont);
    axisX->setLabelsColor(Qt::white);
    axisY->setLabelsFont(labelsFont);
    axisY->setLabelsColor(Qt::white);

    // Set the pen for the spline series
    QColor orange(255, 165, 0);
    QPen pen(orange);
    pen.setWidth(1);
    series_bigOneChart->setPen(pen);

    // Set the chart properties
    chart_bigOneChart->setAxisX(axisX, series_bigOneChart);
    chart_bigOneChart->setAxisY(axisY, series_bigOneChart);
    chart_bigOneChart->setBackgroundBrush(QBrush(Qt::transparent));
    chart_bigOneChart->setPlotAreaBackgroundBrush(QColor(255, 255, 255, 0));
    chart_bigOneChart->setPlotAreaBackgroundVisible(true);
    chart_bigOneChart->setAnimationOptions(QChart::NoAnimation);

    // Create a timer to update the spline series every 80 milliseconds
    QTimer *timer = new QTimer(this);
    timer->setInterval(80);
    int x = 0;
    connect(timer, &QTimer::timeout, [=]() mutable {
        float y = myNamespace::sec_ans;
        QTime currentTime = QTime::currentTime();
        QString currentTimeString = currentTime.toString("hh:mm:ss");
        series_bigOneChart->append(x, y);
        x++;
        if (series_bigOneChart->count() > 20) {
            series_bigOneChart->remove(0);
        }
        chart_bigOneChart->axes(Qt::Horizontal).first()->setRange(x - 20, x);
    });
    timer->start();

    // Create a chart view and set the chart to it
    QChartView *chartView = new QChartView(chart_bigOneChart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set the central widget of the main window to be the chart view
    setCentralWidget(chartView);
}
