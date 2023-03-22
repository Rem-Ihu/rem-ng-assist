#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFrame>
#include <QLabel>
#include <QSvgRenderer>
#include <QStackedWidget>
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QProgressBar>
#include <QSvgRenderer>
#include <QPixmap>
#include <QBrush>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QWidget>
#include <QDate>
#include <QTextCharFormat>
#include <sstream>
#include <QModelIndex>
#include <QPainter>
#include <QPaintEvent>
#include <QProgressBar>
#include <QRectF>
#include <QFont>
#include <QVBoxLayout>
#include <QCalendarWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    AERO CHART////////


    // Create calendar widget
           QCalendarWidget *calendar = new QCalendarWidget(this);

    // Set the text format for the current date with the text "My Text"
        // Set white background for days and gray background for header
        calendar->setStyleSheet("QCalendarWidget QAbstractItemView:enabled:selected { color: black; } \
                                 QCalendarWidget QAbstractItemView:enabled { color: black; } \
                                 QCalendarWidget QWidget#qt_calendar_navigationbar { background-color: #e5e5e5; } \
                                 QCalendarWidget QTableView { background-color: white; } \
                                 QCalendarWidget QHeaderView::section { background-color: #e5e5e5; color: black; } \
                                 QCalendarWidget QToolButton { background-color: transparent; border: none; } \
                                 QCalendarWidget QToolButton:hover { background-color: #dcdcdc; } \
                                 QCalendarWidget QToolButton::menu-indicator { image: url(:/arrow.svg); subcontrol-position: right; subcontrol-origin: padding; } \
                                 QCalendarWidget QMenu { background-color: white; } \
                                 QCalendarWidget QMenu::item:selected { color: black; background-color: #dcdcdc; } \
                                 QCalendarWidget QYearEdit { background-color: white; color: black; } \
                                 QCalendarWidget QSpinBox { color: black; } \
                                 QCalendarWidget QAbstractItemView:enabled:selected:focus { border: none; } \
                                 QCalendarWidget QAbstractItemView:enabled:selected:!focus { border: none; } \
                                 QCalendarWidget QAbstractItemView:focus { border: 1px black;} ");

        // Add calendar widget to layout


                                // Define date and color array
                                    QDate dates[] = { QDate(2023, 3, 3), QDate(2023, 3, 15), QDate(2023, 3, 28), QDate(2023, 3, 31), QDate(2023, 10, 2), QDate(2023, 10, 2), QDate(2023, 6, 9), QDate(2023, 5, 1)};
                                    QColor colors[] = { QColor(48, 172, 255), QColor(255, 125, 33), QColor(161, 66, 255), QColor(152, 8, 8), QColor(12, 207, 100) };

                                    // Loop over dates and set text format for each one
                                    for (int i = 0; i < 5; i++) {
                                        QTextCharFormat format1;
                                        format1.setBackground(QBrush(colors[i]));
                                        calendar->setDateTextFormat(dates[i], format1);
                                     }

                                    // Add calendar widget to layout
                                    ui->TCalendar->setLayout(new QVBoxLayout());
                                    ui->TCalendar->layout()->addWidget(calendar);







    class ProgressBarsFrame : public QWidget {
    public:
        ProgressBarsFrame(QWidget* parent = nullptr) : QWidget(parent) {
            QVBoxLayout* mainLayout = new QVBoxLayout(this);
            QVBoxLayout* progressBarLayout = new QVBoxLayout();

            QLabel* label1 = new QLabel("Progress 1");
            QProgressBar* progressBar1 = new QProgressBar();
            progressBar1->setRange(0, 100);
            progressBar1->setValue(50);   // Value from Firestore
            progressBar1->setStyleSheet("QProgressBar {border-radius: 10px; text-align: left; border: 1px solid grey; color: black;}"
                                        "QProgressBar::chunk { background-color: orange; border-radius: 10px};"
                                        "QProgressBar::chunk:disabled {background-color: lightgrey;}"
                                        "QProgressBar::groove:horizontal {border: 1px solid black; background: black;}"
                                        "QProgressBar::groove:vertical {border: 1px solid black; background: black;}"
                                        "QProgressBar::chunk:horizontal {background: red;}"
                                        "QProgressBar::chunk:vertical {background: red;}"
                                        "QProgressBar::chunk:horizontal:disabled {background: lightgrey;}"
                                        "QProgressBar::chunk:vertical:disabled {background: lightgrey;}"
                                        "QProgressBar::text {color: black;}"
                                        "QProgressBar::text:disabled {color: lightgrey;}");
            QLabel* label2 = new QLabel("Progress 2");
            QProgressBar* progressBar2 = new QProgressBar();
            progressBar2->setRange(0, 100);
            progressBar2->setValue(75);  //Value from Firestore
            progressBar2->setStyleSheet("QProgressBar {border-radius: 10px; text-align: left; border: 1px solid grey; color: black;}"
                                        "QProgressBar::chunk { background-color: red; border-radius: 10px};"
                                        "QProgressBar::chunk:disabled {background-color: lightgrey;}"
                                        "QProgressBar::groove:horizontal {border: 1px solid black; background: black;}"
                                        "QProgressBar::groove:vertical {border: 1px solid black; background: black;}"
                                        "QProgressBar::chunk:horizontal {background: red;}"
                                        "QProgressBar::chunk:vertical {background: red;}"
                                        "QProgressBar::chunk:horizontal:disabled {background: lightgrey;}"
                                        "QProgressBar::chunk:vertical:disabled {background: lightgrey;}"
                                        "QProgressBar::text {color: black;}"
                                        "QProgressBar::text:disabled {color: lightgrey;}");


            QLabel* label3 = new QLabel("Progress 3");
            QProgressBar* progressBar3 = new QProgressBar();
            progressBar3->setRange(0, 100);
            progressBar3->setValue(10);  //Value from Firestore
            progressBar3->setStyleSheet("QProgressBar {border-radius: 10px; text-align: left; border: 1px solid grey; color: black;}"
                                        "QProgressBar::chunk { background-color: green; border-radius: 10px};"
                                        "QProgressBar::chunk:disabled {background-color: lightgrey;}"
                                        "QProgressBar::groove:horizontal {border: 1px solid black; background: black;}"
                                        "QProgressBar::groove:vertical {border: 1px solid black; background: black;}"
                                        "QProgressBar::chunk:horizontal {background: red;}"
                                        "QProgressBar::chunk:vertical {background: red;}"
                                        "QProgressBar::chunk:horizontal:disabled {background: lightgrey;}"
                                        "QProgressBar::chunk:vertical:disabled {background: lightgrey;}"
                                        "QProgressBar::text {color: black;}"
                                        "QProgressBar::text:disabled {color: lightgrey;}");



            progressBarLayout->addWidget(label1);
            progressBarLayout->addWidget(progressBar1);
            progressBarLayout->addWidget(label2);
            progressBarLayout->addWidget(progressBar2);
            progressBarLayout->addWidget(label3);
            progressBarLayout->addWidget(progressBar3);

            mainLayout->addLayout(progressBarLayout);
        }
    };

    // In your MainWindow.cpp file:

    ProgressBarsFrame* progressBarsFrame = new ProgressBarsFrame(this);
    ui->frame_17->setLayout(new QVBoxLayout());
    ui->frame_17->layout()->addWidget(progressBarsFrame);
















    class RadialThermometerProgressBar : public QProgressBar {
    public:
        RadialThermometerProgressBar(QWidget* parent = nullptr) : QProgressBar(parent) {
            setFixedSize(250, 250);
        }

    protected:
        void paintEvent(QPaintEvent* event) override {
            Q_UNUSED(event);
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing, true);

            QRectF rect = this->rect().adjusted(20, 20, -20, -30);
            int minSize = qMin(rect.width(), rect.height());
            int padding = qMax(minSize / 50, 4);
            int fontSize = qMax(minSize / 50, 30);

            QFont font;
            font.setPointSize(fontSize);
            painter.setFont(font);

            // Draw the background circle
            painter.setPen(QPen(QBrush(QColor(Qt::transparent)), padding));
            painter.setBrush(Qt::NoBrush);
            painter.drawEllipse(rect);

            // Draw the progress arc
            painter.setPen(QPen(QBrush(Qt::green), padding * 2));
            painter.setBrush(Qt::NoBrush);
            int value = this->value();
            if (value > minimum() && value < maximum()) {
                int angle = (int)((value - minimum()) * 180.0 / (maximum() - minimum()));
                painter.drawArc(rect, 180 * 16, -angle * 16);
            }

            // Draw the value text
            painter.setPen(QPen(QBrush(Qt::white), padding));
            painter.setBrush(Qt::NoBrush);
            QString valueStr = QString::number(value);
            QRect valueRect = painter.fontMetrics().boundingRect(valueStr);
            painter.drawText(rect.center() - valueRect.center(), valueStr);
        }
    };

    // Create progress bars
    RadialThermometerProgressBar* gauge1 = new RadialThermometerProgressBar(ui->battery_frame_2);
    RadialThermometerProgressBar* gauge2 = new RadialThermometerProgressBar(ui->frame_12);
    RadialThermometerProgressBar* gauge3 = new RadialThermometerProgressBar(ui->prog_bar2_2);
    RadialThermometerProgressBar* gauge4 = new RadialThermometerProgressBar(ui->prog_bar3_2);

    // Set progress bar ranges and values
    gauge1->setRange(0, 100);
    gauge1->setValue(25);

    gauge2->setRange(0, 100);
    gauge2->setValue(50);

    gauge3->setRange(0, 100);
    gauge3->setValue(75);

    gauge4->setRange(0, 100);
    gauge4->setValue(99);

    // Set layouts for frames and add progress bars to frames
    ui->battery_frame_2->setLayout(new QVBoxLayout(ui->battery_frame_2));
    ui->battery_frame_2->layout()->addWidget(gauge1);
    ui->battery_frame_2->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    ui->frame_12->setLayout(new QVBoxLayout(ui->frame_12));
    ui->frame_12->layout()->addWidget(gauge2);
    ui->frame_12->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    ui->prog_bar2_2->setLayout(new QVBoxLayout(ui->prog_bar2_2));
    ui->prog_bar2_2->layout()->addWidget(gauge3);
    ui->prog_bar2_2->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    ui->prog_bar3_2->setLayout(new QVBoxLayout(ui->prog_bar3_2));
    ui->prog_bar3_2->layout()->addWidget(gauge4);
    ui->prog_bar3_2->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));







    QSplineSeries *series_bigOneChart = new QSplineSeries();
    series_bigOneChart->setName("Spline Values");//set the name of the measurement

    series_bigOneChart->append(0, 6);
    series_bigOneChart->append(2, 4);
    series_bigOneChart->append(3, 8);
    series_bigOneChart->append(7, 4);
    series_bigOneChart->append(10, 5);

    *series_bigOneChart << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QChart *chart_bigOneChart = new QChart();
   // chart_bigOneChart->legend()->hide();
    chart_bigOneChart->addSeries(series_bigOneChart);
    chart_bigOneChart->setTitle("Simple spline chart example");
    chart_bigOneChart->createDefaultAxes();
//    chart->setBackgroundBrush(QBrush(QColor("none")));
    //chart_bigOneChart->createDefaultAxes();
  //  chart_bigOneChart->axes(Qt::Vertical).first()->setRange(0, 10);
    chart_bigOneChart->setTitleBrush(QBrush(Qt::black));//customize the color of the title in the chart
    chart_bigOneChart->setBackgroundBrush(QBrush(Qt::white));//customize the color of the background in the chart

    QPen pen(Qt::blue);//customize the color of the series in the chart
    pen.setWidth(1);//customize the width of the series in the chart
    series_bigOneChart->setPen(pen);

// Customize chart background(behind the chart)
//    QLinearGradient backgroundGradient;
//    backgroundGradient.setStart(QPointF(0, 0));
//    backgroundGradient.setFinalStop(QPointF(0, 1));
//    backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
//    backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
//    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart_bigOneChart->setBackgroundBrush(QBrush(::Qt::white));

    // Customize plot area background(in the chart)
//    QLinearGradient plotAreaGradient;
//    plotAreaGradient.setStart(QPointF(0, 1));
//    plotAreaGradient.setFinalStop(QPointF(1, 0));
//    plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
//    plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
//    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart_bigOneChart->setPlotAreaBackgroundBrush(QColor(255, 255, 255, 0));
    chart_bigOneChart->setPlotAreaBackgroundVisible(true);

    QCategoryAxis *axisX = new QCategoryAxis();
    QCategoryAxis *axisY = new QCategoryAxis();

    QFont labelsFont;
    labelsFont.setPixelSize(12);
    axisX->setLabelsFont(labelsFont);
    axisX->setLabelsColor(Qt::white);
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
//    axisX->append("<span style=\"color: #339966;\">low</span>", 7);
//    axisX->append("<span style=\"color: #330066;\">optimal</span>", 14);
//    axisX->append("<span style=\"color: #55ff66;\">high</span>", 20);


//    axisY->append("<font color=\"red\">slow</font>", 3);
//    axisY->append("<font color=\"green\">med</font>", 7);
//    axisY->append("<span style=\"color: #ffff00;\">fast</span>", 10);

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
    chartView_bigOneChart->setBackgroundBrush(QBrush());
//    chartView->setBackgroundBrush(QBrush(QColor("salmon")));

    QVBoxLayout *layout_bigOneChart1 = new QVBoxLayout(ui->bigOneChart);
    layout_bigOneChart1->addWidget(chartView_bigOneChart);


    //AREA CHART

    QLineSeries *series0 = new QLineSeries();
    series0->setName("Area Chart Values");
    *series0 << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7) << QPointF(12, 6)
             << QPointF(16, 7) << QPointF(18, 5);


    timer_2 = new QTimer(this);
        connect(timer_2, &QTimer::timeout, this, &MainWindow::advanceSlideshow);
        timer_2->start(3500);


    QAreaSeries *area_series = new QAreaSeries(series0);//, series1);
    series0->setName("Area Chart");
    QPen pen1(0x111110);
    pen1.setWidth(2);
    area_series->setPen(pen1);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(0.0, 0xf9f6f3);
    gradient.setColorAt(1.0, 0xa3a2a1);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    area_series->setBrush(gradient);

    QChart *area_chart = new QChart();
    area_chart->addSeries(area_series);
    area_chart->setTitle("Simple areachart example");
    area_chart->createDefaultAxes();
    area_chart->axes(Qt::Horizontal).first()->setRange(0, 20);
    area_chart->axes(Qt::Vertical).first()->setRange(0, 10);
    area_chart->setTitleBrush(QBrush(Qt::black));//customize the color of the title in the chart
    area_chart->setBackgroundBrush(QBrush(Qt::white));//customize the color of the background in the chart
    area_chart->setPlotAreaBackgroundBrush(QColor(255, 255, 255, 0));
    area_chart->setPlotAreaBackgroundVisible(true);

    QGraphicsDropShadowEffect *shadow_area_chart = new QGraphicsDropShadowEffect;
    shadow_area_chart->setBlurRadius(15);
    shadow_area_chart->setColor(QColor(0, 0, 0, 60));
    shadow_area_chart->setOffset(0.5, 0);
    frame->setGraphicsEffect(shadow_area_chart);

    chart_bigOneChart->setAnimationOptions(QChart::SeriesAnimations);


    QChartView *chartView_areaChart = new QChartView(area_chart);
    chartView_areaChart->setRenderHint(QPainter::Antialiasing);
    chartView_areaChart->setBackgroundBrush(QBrush());

    QVBoxLayout *layout_bigOneChart = new QVBoxLayout(ui->area_chart);
    layout_bigOneChart->addWidget(chartView_areaChart);
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


//void MainWindow::on_pushButtonSettings_clicked()
//{
//    ui->stackedWidget->setCurrentIndex(6);
//}


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
void MainWindow::on_pushButton_Viewmore_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
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




void MainWindow::advanceSlideshow()
{
    int nextIndex = (ui->SlideshowWid->currentIndex() + 1) % ui->SlideshowWid->count();
    QWidget* nextPage = ui->SlideshowWid->widget(nextIndex);

    // Create QGraphicsOpacityEffect object and set the opacity to 0
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(nextPage);
    nextPage->setGraphicsEffect(effect);
    effect->setOpacity(0.0);

    // Create the animation and connect the finished() signal to the slot
    QPropertyAnimation* animFadeOut = new QPropertyAnimation(ui->SlideshowWid->currentWidget()->graphicsEffect(), "opacity");
    animFadeOut->setDuration(1000);
    animFadeOut->setStartValue(1.0);
    animFadeOut->setEndValue(0.0);

    QPropertyAnimation* animFadeIn = new QPropertyAnimation(effect, "opacity");
    animFadeIn->setDuration(1000);
    animFadeIn->setStartValue(0.0);
    animFadeIn->setEndValue(1.0);

    connect(animFadeOut, &QPropertyAnimation::finished, this, [=]() {
        ui->SlideshowWid->setCurrentIndex(nextIndex);
        animFadeIn->start();
    });

    // Start the animations
    animFadeOut->start();
}



