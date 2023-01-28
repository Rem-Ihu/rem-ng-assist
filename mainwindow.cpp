#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui_mainwindow.h"

#include <QStackedWidget>
#include <iostream>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QSplineSeries *series_bigOneChart = new QSplineSeries();
    series_bigOneChart->setName("spline");

    series_bigOneChart->append(0, 6);
    series_bigOneChart->append(2, 4);
    series_bigOneChart->append(3, 8);
    series_bigOneChart->append(7, 4);
    series_bigOneChart->append(10, 5);

    *series_bigOneChart << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QChart *chart_bigOneChart = new QChart();
    chart_bigOneChart->legend()->hide();
    chart_bigOneChart->addSeries(series_bigOneChart);
    chart_bigOneChart->setTitle("Simple spline chart example");
//    chart->setBackgroundBrush(QBrush(QColor("none")));
    //chart_bigOneChart->createDefaultAxes();
  //  chart_bigOneChart->axes(Qt::Vertical).first()->setRange(0, 10);
    chart_bigOneChart->setTitleBrush(QBrush(Qt::white));//customize the color of the title in the chart
    chart_bigOneChart->setBackgroundBrush(QBrush(Qt::white));//customize the color of the background in the chart

    QPen pen(Qt::blue);//customize the color of the series in the chart
    pen.setWidth(1);//customize the width of the series in the chart
    series_bigOneChart->setPen(pen);

    // Customize chart background(behind the chart)
    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
    backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart_bigOneChart->setBackgroundBrush(backgroundGradient);

    // Customize plot area background(in the chart)
    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
    plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart_bigOneChart->setPlotAreaBackgroundBrush(plotAreaGradient);
    chart_bigOneChart->setPlotAreaBackgroundVisible(true);

    QCategoryAxis *axisX = new QCategoryAxis();
    QCategoryAxis *axisY = new QCategoryAxis();

    QFont labelsFont;
    labelsFont.setPixelSize(12);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);

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
    axisX->append("<span style=\"color: #339966;\">low</span>", 7);
    axisX->append("<span style=\"color: #330066;\">optimal</span>", 14);
    axisX->append("<span style=\"color: #55ff66;\">high</span>", 20);


    axisY->append("<font color=\"red\">slow</font>", 3);
    axisY->append("<font color=\"green\">med</font>", 7);
    axisY->append("<span style=\"color: #ffff00;\">fast</span>", 10);

//    axisX->setRange(0, 20);
//    axisY->setRange(0, 10);

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

    chart_bigOneChart->setAnimationOptions(QChart::SeriesAnimations);
    QChartView *chartView_bigOneChart = new QChartView(chart_bigOneChart);
    chartView_bigOneChart->setRenderHint(QPainter::Antialiasing);
//    chartView->setBackgroundBrush(QBrush(QColor("salmon")));

    QVBoxLayout *layout_bigOneChart1 = new QVBoxLayout(ui->frame_3);
    layout_bigOneChart1->addWidget(chartView_bigOneChart);


    QVBoxLayout *layout_bigOneChart = new QVBoxLayout(ui->bigOneChart);
    layout_bigOneChart->addWidget(chartView_bigOneChart);

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


    while (std::getline(ss_pref, preferences_split_part, ':')) {
        preferences_split.push_back(preferences_split_part); //pushing the values in the vector
    }

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
    }else{
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

