#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui_mainwindow.h"

#include <QStackedWidget>
#include <iostream>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QSplineSeries *series = new QSplineSeries();
    series->setName("spline");

    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);

    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("Simple spline chart example");
//    chart->setBackgroundBrush(QBrush(QColor("none")));
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, 10);

    QFrame *frame = ui->bigOneChart;
    //creating a drop shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(15);
    shadow->setColor(QColor(0, 0, 0, 60));
    shadow->setOffset(0.5, 0);
    frame->setGraphicsEffect(shadow);

    chart->setAnimationOptions(QChart::SeriesAnimations);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
//    chartView->setBackgroundBrush(QBrush(QColor("salmon")));
    QVBoxLayout *layout = new QVBoxLayout(ui->bigOneChart);
    layout->addWidget(chartView);

    QScrollArea *scrollArea_Home = new QScrollArea;
    scrollArea_Home->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//    QGraphicsScene *scene = new QGraphicsScene();
//    QGraphicsView *Slideshow = new QGraphicsView(scene);

//    QPixmap pixmap1("merch_icon.png");
//    QPixmap pixmap2("news_icon.png");
//    scene->addPixmap(pixmap1);
//    QTimer *timer = new QTimer();
//    connect(timer, &QTimer::timeout, &scene, &QGraphicsScene::updateSlide);
//    timer->start(5000);


//    QOpenGLWidget * <to_onoma_pou_tha_dwseis> = new QOpenGLWidget(<onoma_tou_ui>-><onoma_openglwidget_apo_to_mainwindow.ui>);

//    //+++++++++++++++++++++++++++++++++++++++++++

//    QLineSeries *series2 = new QLineSeries();

//    series2->append(0, 6);
//    series2->append(2, 4);
//    series2->append(3, 8);
//    series2->append(7, 4);
//    series2->append(10, 5);

//    *series2 << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3)
//            << QPointF(20, 2);

//    QChart *chart2 = new QChart();
//    chart2->legend()->hide();
//    chart2->addSeries(series2);
//    chart2->createDefaultAxes();
//    chart2->setTitle("Line Chart Example");


//    chart2->setAnimationOptions(QChart::SeriesAnimations);
//    QChartView *chartView2 = new QChartView(chart2);
//    chartView2->setRenderHint(QPainter::Antialiasing);
//    QVBoxLayout *layout2 = new QVBoxLayout(ui->frame2);
//    layout2->addWidget(chartView2);


//    //+++++++++++++++++++++++++++++++++++++++++++


//    QBarSet *set0 = new QBarSet("Jane");
//    QBarSet *set1 = new QBarSet("John");
//    QBarSet *set2 = new QBarSet("Axel");
//    QBarSet *set3 = new QBarSet("Mary");
//    QBarSet *set4 = new QBarSet("Samantha");

//    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
//    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
//    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
//    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
//    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

//    QBarSeries *series3 = new QBarSeries();

//    series3->append(set0);
//    series3->append(set1);
//    series3->append(set2);
//    series3->append(set3);
//    series3->append(set4);


//    QChart *chart3 = new QChart();
//    chart3->addSeries(series3);
//    chart3->setTitle("Simple barchart example");
//    chart3->setAnimationOptions(QChart::SeriesAnimations);


//    QStringList categories;

//    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
//    QBarCategoryAxis *axisX = new QBarCategoryAxis();
//    axisX->append(categories);
//    chart3->addAxis(axisX, Qt::AlignBottom);
//    series3->attachAxis(axisX);

//    QValueAxis *axisY = new QValueAxis();
//    axisY->setRange(0,15);
//    chart3->addAxis(axisY, Qt::AlignLeft);
//    series3->attachAxis(axisY);


//    chart3->legend()->setVisible(true);
//    chart3->legend()->setAlignment(Qt::AlignBottom);


//    QChartView *chartView3 = new QChartView(chart3);
//    chartView3->setRenderHint(QPainter::Antialiasing);
//    QVBoxLayout *layout3 = new QVBoxLayout(ui->frame3);
//    layout3->addWidget(chartView3);


//    //+++++++++++++++++++++++++++++++++++++++++++



//    QBarSet *set01 = new QBarSet("Jane");

//    QBarSet *set11 = new QBarSet("John");
//    QBarSet *set21 = new QBarSet("Axel");
//    QBarSet *set31 = new QBarSet("Mary");
//    QBarSet *set41 = new QBarSet("Samantha");

//    *set01 << 1 << 2 << 3 << 4 << 5 << 6;
//    *set11 << 5 << 0 << 0 << 4 << 0 << 7;
//    *set21 << 3 << 5 << 8 << 13 << 8 << 5;
//    *set31 << 5 << 6 << 7 << 3 << 4 << 5;
//    *set41 << 9 << 7 << 5 << 3 << 1 << 2;


//    QPercentBarSeries *series4 = new QPercentBarSeries();
//    series4->append(set01);
//    series4->append(set11);
//    series4->append(set21);
//    series4->append(set31);
//    series4->append(set41);


//    QChart *chart4 = new QChart();
//    chart4->addSeries(series4);
//    chart4->setTitle("Simple percentbarchart example");
//    chart4->setAnimationOptions(QChart::SeriesAnimations);

//    QStringList categories2;
//    categories2 << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
//    QBarCategoryAxis *axisX2 = new QBarCategoryAxis();
//    axisX->append(categories2);
//    chart4->addAxis(axisX2, Qt::AlignBottom);
//    series4->attachAxis(axisX);
//    QValueAxis *axisY2 = new QValueAxis();
//    chart4->addAxis(axisY2, Qt::AlignLeft);
//    series4->attachAxis(axisY);

//    chart4->legend()->setVisible(true);
//    chart4->legend()->setAlignment(Qt::AlignBottom);

//    QChartView *chartView4 = new QChartView(chart4);
//    chartView4->setRenderHint(QPainter::Antialiasing);
//    QVBoxLayout *layout4 = new QVBoxLayout(ui->frame4);
//    layout4->addWidget(chartView4);


//    QFrame *frame1 = ui->buttonFrameAll;
//    QPropertyAnimation *animation = new QPropertyAnimation(frame1, "geometry");
//    animation->setDuration(500);
//    animation->setStartValue(QRect(0, 0, 250, 16777215));
//    animation->setEndValue(QRect(0, 0, 0, 16777215));


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
void MainWindow::on_Button_recent_charts_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
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

