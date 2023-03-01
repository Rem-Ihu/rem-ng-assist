#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui_mainwindow.h"
#include <QSvgRenderer>
#include <QStackedWidget>
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSvgRenderer>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QFont>
#include <QPalette>
#include <QLegendMarker>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <variant>





namespace myNamespace{
    extern float fin_ans,sec_ans,ok;
}

namespace myNamespace2{
    extern int N;
    extern double* array;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //AERO CHART SETUP
    QSplineSeries *series_bigOneChart = new QSplineSeries();//create the series for the aero chart
    series_bigOneChart->setName("Real Time Values");//set the name of the measurement




    QChart *chart_bigOneChart = new QChart();//create the aero chart
    chart_bigOneChart->addSeries(series_bigOneChart); //add the values
    QFont titleFont("Arial", 16, QFont::Bold); // Create a QFont object with desired font family, size, and weight
    chart_bigOneChart->setTitle("Real Time Chart"); // Set the chart title
    chart_bigOneChart->setTitleFont(titleFont); // Set the font of the chart title
    chart_bigOneChart->createDefaultAxes(); //create the axes
    chart_bigOneChart->axes(Qt::Vertical).first()->setRange(-7, 12); //set the range of values of axis y
    chart_bigOneChart->setTitleBrush(QBrush(Qt::white));//customize the color of the title in the chart
    chart_bigOneChart->setBackgroundBrush(QBrush(Qt::transparent));//customize the color of the background in the chart

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



    chart_bigOneChart->setPlotAreaBackgroundBrush(QColor(255, 255, 255, 0));// set the color of the plot area to trasnparent
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
    QPen axisPen(Qt::black);
    axisPen.setWidth(5);
    axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);

    // Customize axis label colors
    QBrush axisBrush(Qt::yellow);
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    QTextCharFormat format;
    format.setForeground(Qt::blue);
    axisX->setLabelsColor(Qt::blue);
    axisY->setLabelsColor(Qt::blue);


    chart_bigOneChart->addAxis(axisX, Qt::AlignBottom);
    chart_bigOneChart->addAxis(axisY, Qt::AlignLeft);
    //chart_bigOneChart->setAxisX(axisX);
    series_bigOneChart->attachAxis(axisX);
    series_bigOneChart->attachAxis(axisY);


    QFrame *frame = ui->bigOneChart_2;
    //creating a drop shadow effect
    QGraphicsDropShadowEffect *shadow_bigOneChart = new QGraphicsDropShadowEffect;
    shadow_bigOneChart->setBlurRadius(15);
    shadow_bigOneChart->setColor(QColor(0, 0, 0, 60));
    shadow_bigOneChart->setOffset(0.5, 0);
    frame->setGraphicsEffect(shadow_bigOneChart);


    QChartView *chartView_bigOneChart = new QChartView(chart_bigOneChart);
    chartView_bigOneChart->setRenderHint(QPainter::Antialiasing);
    chartView_bigOneChart->setBackgroundBrush(QBrush());
//    chartView->setBackgroundBrush(QBrush(QColor("salmon")));

    QVBoxLayout *layout_bigOneChart1 = new QVBoxLayout(ui->bigOneChart_2);
    layout_bigOneChart1->addWidget(chartView_bigOneChart);


    //AERO CHART SETUP

//    QSplineSeries *series_bigOneChart = new QSplineSeries();//create the series for the aero chart
//    series_bigOneChart->setName("Spline Values");//set the name of the measurement


//    QChart *chart_bigOneChart = new QChart();//create the aero chart
//    chart_bigOneChart->addSeries(series_bigOneChart); //add the values
//    chart_bigOneChart->setTitle("Simple spline chart example"); //create a label for it
//    chart_bigOneChart->createDefaultAxes(); //create the axes
//    chart_bigOneChart->axes(Qt::Vertical).first()->setRange(-7, 12); //set the range of values of axis y
//    chart_bigOneChart->setTitleBrush(QBrush(Qt::white));//customize the color of the title in the chart
//    chart_bigOneChart->setBackgroundBrush(QBrush(Qt::transparent));//customize the color of the background in the chart

//    QColor orange(255, 165, 0); // RGB values for orange
//    QPen pen(orange);//customize the color of the series in the chart--create the color layer
//    pen.setWidth(1);//customize the width of the series in the chart
//    series_bigOneChart->setPen(pen); //apply the color to the series

//    // Create a QTimer object and set its interval to 500 milliseconds (0.5 seconds)
//    QTimer *timer = new QTimer(this); //create a timer
//    timer->setInterval(80); //to 80 milliseconds

//    int x = 0;

//    // Add the first 10 data points
//    for (int i = 0; i < 10; i++) {
//        float y = myNamespace::sec_ans;
//        series_bigOneChart->append(x, y);
//        x++;
//    }

//    // Connect the timeout() signal of the timer to a lambda function that generates
//    // random numbers and updates the chart
//    connect(timer, &QTimer::timeout, [=]() mutable {
//        // Generate a random number between 1 and 10
//        float y = myNamespace::sec_ans;

//        // Append the new data point
//        QTime currentTime = QTime::currentTime();
//        QString currentTimeString = currentTime.toString("hh:mm:ss");
////        series_bigOneChart->append("<span style=\"color: #000000;\">"+currentTimeString+"</span>", y);
//        series_bigOneChart->append(x, y);
//        x++;

//        // Remove the first data point if the series has more than 20 points
//        if (series_bigOneChart->count() > 20) {
//            series_bigOneChart->remove(0);
//        }

//        // Update the X range of the chart to show the last 20 data points
//        chart_bigOneChart->setAnimationOptions(QChart::NoAnimation);
//        chart_bigOneChart->axes(Qt::Horizontal).first()->setRange(x - 20, x);
//    });

//    // Start the timer
//    timer->start();



//    chart_bigOneChart->setPlotAreaBackgroundBrush(QColor(255, 255, 255, 0));// set the color of the plot area to trasnparent
//    chart_bigOneChart->setPlotAreaBackgroundVisible(true); //set the application layer to visible
//    chart_bigOneChart->setAnimationOptions(QChart::NoAnimation); //disable the animation for a smoother transition from point to point
//    QCategoryAxis *axisX = new QCategoryAxis();//create the 2 axes
//    QCategoryAxis *axisY = new QCategoryAxis();

//    QFont labelsFont; //create a font
//    labelsFont.setPixelSize(12); //set the size of the letters
//    axisX->setLabelsFont(labelsFont); //apply to axis x
//    axisX->setLabelsColor(Qt::white); //change the color
//    axisY->setLabelsFont(labelsFont); //apply to axis y

//    // Customize axis colors
//    QPen axisPen(Qt::black);
//    axisPen.setWidth(5);
//    axisX->setLinePen(axisPen);
//    axisY->setLinePen(axisPen);

//    // Customize axis label colors
//    QBrush axisBrush(Qt::yellow);
//    axisX->setLabelsBrush(axisBrush);
//    axisY->setLabelsBrush(axisBrush);

//    QTextCharFormat format;
//    format.setForeground(Qt::blue);
//    axisX->setLabelsColor(Qt::blue);
//    axisY->setLabelsColor(Qt::blue);


//    chart_bigOneChart->addAxis(axisX, Qt::AlignBottom);
//    chart_bigOneChart->addAxis(axisY, Qt::AlignLeft);
//    //chart_bigOneChart->setAxisX(axisX);
//    series_bigOneChart->attachAxis(axisX);
//    series_bigOneChart->attachAxis(axisY);


//    QFrame *frame = ui->bigOneChart;
//    //creating a drop shadow effect
//    QGraphicsDropShadowEffect *shadow_bigOneChart = new QGraphicsDropShadowEffect;
//    shadow_bigOneChart->setBlurRadius(15);
//    shadow_bigOneChart->setColor(QColor(0, 0, 0, 60));
//    shadow_bigOneChart->setOffset(0.5, 0);
//    frame->setGraphicsEffect(shadow_bigOneChart);


//    QChartView *chartView_bigOneChart = new QChartView(chart_bigOneChart);
//    chartView_bigOneChart->setRenderHint(QPainter::Antialiasing);
//    chartView_bigOneChart->setBackgroundBrush(QBrush());
////    chartView->setBackgroundBrush(QBrush(QColor("salmon")));

//    QVBoxLayout *layout_bigOneChart1 = new QVBoxLayout(ui->bigOneChart);
//    layout_bigOneChart1->addWidget(chartView_bigOneChart);


//    //AERO CHART CUSTOMIZATIONS
//    //GRADIENT
//    // Customize chart background(the area behind the chart and the plot)
////    QLinearGradient backgroundGradient;
////    backgroundGradient.setStart(QPointF(0, 0));
////    backgroundGradient.setFinalStop(QPointF(0, 1));
////    backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
////    backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
////    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);

//    // Customize plot area background(in the chart-the plot area)
////    QLinearGradient plotAreaGradient;
////    plotAreaGradient.setStart(QPointF(0, 1));
////    plotAreaGradient.setFinalStop(QPointF(1, 0));
////    plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
////    plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
////    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);

//    //Customize the axes colors and format as well
//    //    axisX->append("<span style=\"color: #339966;\">low</span>", 7);
//    //    axisX->append("<span style=\"color: #330066;\">optimal</span>", 14);
//    //    axisX->append("<span style=\"color: #55ff66;\">high</span>", 20);


//    //    axisY->append("<font color=\"red\">slow</font>", 3);
//    //    axisY->append("<font color=\"green\">med</font>", 7);
//    //    axisY->append("<span style=\"color: #ffff00;\">fast</span>", 10);

//    //    axisX->setRange(0, 20);
//    //    axisY->setRange(0, 10);

    //AREA CHART





    for(int i=0; i<myNamespace2::N; i++)
        qDebug() << "HEREEEEE--->" << myNamespace2::array[i];


    // Create a chart object
    QChart *chart = new QChart();

    // Create a line series object and add the values from the vector
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < myNamespace2::N; i++) {
        series->append(i + 0.5, myNamespace2::array[i]);
    }

    // Add the line series to the chart
    chart->addSeries(series);

    // Set up the X-axis with 0.5 increments
    QValueAxis *axisX1 = new QValueAxis();
    axisX1->setTickCount(myNamespace2::N);
    axisX1->setLabelFormat("%.1f");
    axisX1->setRange(0, myNamespace2::N);
    axisX1->setTickInterval(0.5);
    chart->addAxis(axisX1, Qt::AlignBottom);
    series->attachAxis(axisX1);

    // Set up the Y-axis
    QValueAxis *axisY1 = new QValueAxis();
    chart->addAxis(axisY1, Qt::AlignLeft);
    series->attachAxis(axisY1);

    // Set the title of the chart
    chart->setTitle("My Chart");

    // Create a chart view object and set the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);

    QVBoxLayout *layout_bigOneChart2 = new QVBoxLayout(ui->area_chart);
    layout_bigOneChart2->addWidget(chartView);




}

MainWindow::~MainWindow()
{
    delete ui;
}

//starting button signals for the stacked widget. ======
void MainWindow::on_pushButtonRealTimeData_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButtonCharts_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton3DBikeView_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButtonNews_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButtonMerch_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButtonSettings_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_pushButtonOthers_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_pushButtonAboutUs_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_pushButtonContact_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}


void MainWindow::on_pushButtonHome_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//adding new tabs! ========================================
void MainWindow::on_addTabNameButton_clicked()
{
    //making the widgets in ui
    QTabWidget* tabWidget = ui->tabChartWidget;
    QLineEdit* lineEdit = ui->nametab;

    //getting the text from the LineEdit
    QString tabName = lineEdit->text();

    std::string whole_preference = tabName.toStdString(); //converting the string from QString to normal string.
    std::vector<std::string> preferences_split; // using vectors to have the preferences split from the whole string.

    std::stringstream ss_pref(whole_preference); //using stringstream to be able to use the getline to split the string.
    std::string preferences_split_part; //the parts that are going to be pushed back to the vector

    if(whole_preference.size()!=0)
        while (std::getline(ss_pref, preferences_split_part, ':')) {
            preferences_split.push_back(preferences_split_part); //pushing the values in the vector
        }
    else
        return;

    QWidget *tabContent = new QWidget; //makes a widget for the tab window

    QGridLayout *layout = new QGridLayout; //makes the layout be a grid
    tabContent->setLayout(layout); //setting the layout of the widget


    if(std::stoi(preferences_split.at(1)) == 1){
        QFrame *label1 = new QFrame;
        label1->setStyleSheet("QFrame { background-color: blue; }");
        layout->addWidget(label1, 0, 0);
    }else if (std::stoi(preferences_split.at(1)) == 2){
        QFrame *label1 = new QFrame;
        QFrame *label2 = new QFrame;
        label1->setStyleSheet("QFrame { background-color: blue; }");
        label2->setStyleSheet("QFrame { background-color: red; }"); //styling the frames
        layout->addWidget(label1, 0, 0);
        layout->addWidget(label2, 0, 1);

    }else if(std::stoi(preferences_split.at(1)) == 3){
        QFrame *label1 = new QFrame;
        QFrame *label2 = new QFrame;
        QFrame *label3 = new QFrame;
        label1->setStyleSheet("QFrame { background-color: blue; }");
        label2->setStyleSheet("QFrame { background-color: red; }"); //styling the frames
        label3->setStyleSheet("QFrame { background-color: black; }");
        layout->addWidget(label1, 0, 0);
        layout->addWidget(label2, 0, 1);
        layout->addWidget(label3, 1, 0, 1, 2); //puting the frames like a 2x2 pinaka
        //1 = position x, 0 = position y, 1 = number of rows that the label is able to acumulate, 2 = number of rows antistoixa
    }else if(std::stoi(preferences_split.at(1)) == 4){
        QFrame *label1 = new QFrame;
        QFrame *label2 = new QFrame;
        QFrame *label3 = new QFrame;
        QFrame *label4 = new QFrame;
        label1->setStyleSheet("QFrame { background-color: blue; }");
        label2->setStyleSheet("QFrame { background-color: red; }"); //styling the frames
        label3->setStyleSheet("QFrame { background-color: black; }");
        label4->setStyleSheet("QFrame { background-color: green; }");
        layout->addWidget(label1, 0, 0);
        layout->addWidget(label2, 0, 1);
        layout->addWidget(label3, 1, 0); //puting the frames like a 2x2 pinaka
        layout->addWidget(label4, 1, 1);
    }else{
        qDebug() << "NOPE";
    }

    QString final_name = QString::fromStdString(preferences_split.at(0));

    //adding a new tab to the TabWidget
    int tabIndex = tabWidget->addTab(tabContent, final_name);

    //setting the name of the new tab
    tabWidget->setTabText(tabIndex, final_name);
}

//removing selected tab! ==================================
void MainWindow::on_tabChartWidget_tabCloseRequested(int index)
{
    QTabWidget* tabWidget = ui->tabChartWidget;
    tabWidget->removeTab(index);
}



void MainWindow::on_pushButtonErrorPopUp_clicked()
{
    QMessageBox messageBox;
    messageBox.setText("ERROR");
    messageBox.setIcon(QMessageBox::Critical);
    messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    messageBox.setDefaultButton(QMessageBox::Ok);
    messageBox.exec();
}

