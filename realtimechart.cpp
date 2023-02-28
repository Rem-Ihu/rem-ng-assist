#include "realtimechart.h"
#include <QSvgRenderer>
#include <QStackedWidget>
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

namespace myNamespace{
    extern float fin_ans,sec_ans,ok;

}

RealTImeChart::RealTImeChart(QWidget *parent)
    : QMainWindow{parent}
{
    //AERO CHART SETUP

    QSplineSeries *series_bigOneChart = new QSplineSeries();//create the series for the aero chart
    series_bigOneChart->setName("Spline Values");//set the name of the measurement

    qDebug() << myNamespace::sec_ans ; //testing for real time data

    QChart *chart_bigOneChart = new QChart();//create the aero chart
    chart_bigOneChart->legend()->setColor(Qt::white); //hide the legend of the chart
    chart_bigOneChart->addSeries(series_bigOneChart); //add the values
    chart_bigOneChart->setTitle("Simple spline chart example"); //create a label for it
    chart_bigOneChart->createDefaultAxes(); //create the axes
    chart_bigOneChart->axes(Qt::Vertical).first()->setRange(-7, 12); //set the range of values of axis y
    chart_bigOneChart->setTitleBrush(QBrush(Qt::white));//customize the color of the title in the chart
    chart_bigOneChart->setBackgroundBrush(Qt::transparent);//customize the color of the background in the chart

    QColor orange(255, 165, 0); // RGB values for orange
    QPen pen(orange);//customize the color of the series in the chart--create the color layer
    pen.setWidth(1);//customize the width of the series in the chart
    series_bigOneChart->setPen(pen); //apply the color to the series

    // Create a QTimer object and set its interval to 500 milliseconds (0.5 seconds)
    QTimer *timer = new QTimer(this); //create a timer
    timer->setInterval(80); //to 80 milliseconds

    int x = 0;

    // Add the first 10 data points
    for (int i = 0; i < 10; i++) {
        float y = myNamespace::sec_ans;
        series_bigOneChart->append(x, y);
        x++;
    }

    // Connect the timeout() signal of the timer to a lambda function that generates
    // random numbers and updates the chart
    connect(timer, &QTimer::timeout, [=]() mutable {
        // Generate a random number between 1 and 10
        float y = myNamespace::sec_ans;

        // Append the new data point
        QTime currentTime = QTime::currentTime();
        QString currentTimeString = currentTime.toString("hh:mm:ss");
//        series_bigOneChart->append("<span style=\"color: #000000;\">"+currentTimeString+"</span>", y);
        series_bigOneChart->append(x, y);
        x++;

        // Remove the first data point if the series has more than 20 points
        if (series_bigOneChart->count() > 20) {
            series_bigOneChart->remove(0);
        }

        // Update the X range of the chart to show the last 20 data points
        chart_bigOneChart->setAnimationOptions(QChart::NoAnimation);
        chart_bigOneChart->axes(Qt::Horizontal).first()->setRange(x - 20, x);
    });

    // Start the timer
    timer->start();



    chart_bigOneChart->setPlotAreaBackgroundBrush(Qt::transparent);// set the color of the plot area to trasnparent
    chart_bigOneChart->setPlotAreaBackgroundVisible(true); //set the application layer to visible
    chart_bigOneChart->setAnimationOptions(QChart::NoAnimation); //disable the animation for a smoother transition from point to point
    QCategoryAxis *axisX = new QCategoryAxis();//create the 2 axes
    QCategoryAxis *axisY = new QCategoryAxis();

    QFont labelsFont; //create a font
    labelsFont.setPixelSize(12); //set the size of the letters
    axisX->setLabelsFont(labelsFont); //apply to axis x
    axisX->setLabelsColor(Qt::white); //change the color
    axisY->setLabelsFont(labelsFont); //apply to axis y

    // Customize axis colors
    QPen axisPen(Qt::white);
    axisPen.setWidth(5);
    axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);

    // Customize axis label colors
    QBrush axisBrush(Qt::white);
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    QTextCharFormat format;
    format.setForeground(Qt::white);
    axisX->setLabelsColor(Qt::white);
    axisY->setLabelsColor(Qt::white);


    chart_bigOneChart->addAxis(axisX, Qt::AlignBottom);
    chart_bigOneChart->addAxis(axisY, Qt::AlignLeft);
    //chart_bigOneChart->setAxisX(axisX);
    series_bigOneChart->attachAxis(axisX);
    series_bigOneChart->attachAxis(axisY);


    QFrame *frame = ui->bigOneChart;
    //creating a drop shadow effect
    QGraphicsDropShadowEffect *shadow_bigOneChart = new QGraphicsDropShadowEffect;
    shadow_bigOneChart->setBlurRadius(15);
    shadow_bigOneChart->setColor(QColor(0, 0, 0, 60));
    shadow_bigOneChart->setOffset(0.5, 0);
    frame->setGraphicsEffect(shadow_bigOneChart);


    QChartView *chartView_bigOneChart = new QChartView(chart_bigOneChart);
    chartView_bigOneChart->setRenderHint(QPainter::Antialiasing);
    chartView_bigOneChart->setBackgroundBrush(Qt::transparent);
//    chartView->setBackgroundBrush(QBrush(QColor("salmon")));

    QVBoxLayout *layout_bigOneChart1 = new QVBoxLayout(ui->bigOneChart);
    layout_bigOneChart1->addWidget(chartView_bigOneChart);


    //AERO CHART CUSTOMIZATIONS
    //GRADIENT
    // Customize chart background(the area behind the chart and the plot)
//    QLinearGradient backgroundGradient;
//    backgroundGradient.setStart(QPointF(0, 0));
//    backgroundGradient.setFinalStop(QPointF(0, 1));
//    backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
//    backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
//    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    // Customize plot area background(in the chart-the plot area)
//    QLinearGradient plotAreaGradient;
//    plotAreaGradient.setStart(QPointF(0, 1));
//    plotAreaGradient.setFinalStop(QPointF(1, 0));
//    plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
//    plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
//    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    //Customize the axes colors and format as well
    //    axisX->append("<span style=\"color: #339966;\">low</span>", 7);
    //    axisX->append("<span style=\"color: #330066;\">optimal</span>", 14);
    //    axisX->append("<span style=\"color: #55ff66;\">high</span>", 20);


    //    axisY->append("<font color=\"red\">slow</font>", 3);
    //    axisY->append("<font color=\"green\">med</font>", 7);
    //    axisY->append("<span style=\"color: #ffff00;\">fast</span>", 10);

    //    axisX->setRange(0, 20);
    //    axisY->setRange(0, 10);
}
