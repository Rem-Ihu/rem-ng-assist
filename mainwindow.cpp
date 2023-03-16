#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui_mainwindow.h"
#include "databasehandler1.h"
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
#include <QTimer>
#include <QFont>
#include <QPalette>
#include <QLegendMarker>
#include <QSemaphore>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <variant>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtGui/QPainter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
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
                                   ui->teamCalendar->setLayout(new QVBoxLayout());
                                   ui->teamCalendar->layout()->addWidget(calendar);






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
    ui->bars_frame->setLayout(new QVBoxLayout());
    ui->bars_frame->layout()->addWidget(progressBarsFrame);
















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
    // Create progress bars
    RadialThermometerProgressBar* gauge1 = new RadialThermometerProgressBar(ui->frame_4);
    RadialThermometerProgressBar* gauge2 = new RadialThermometerProgressBar(ui->battery_frame);
    RadialThermometerProgressBar* gauge3 = new RadialThermometerProgressBar(ui->prog_bar2);
    RadialThermometerProgressBar* gauge4 = new RadialThermometerProgressBar(ui->prog_bar3);

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
    ui->frame_4->setLayout(new QVBoxLayout(ui->frame_4));
    ui->frame_4->layout()->addWidget(gauge1);
    ui->frame_4->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    ui->battery_frame->setLayout(new QVBoxLayout(ui->battery_frame));
    ui->battery_frame->layout()->addWidget(gauge2);
    ui->battery_frame->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    ui->prog_bar2->setLayout(new QVBoxLayout(ui->prog_bar2));
    ui->prog_bar2->layout()->addWidget(gauge3);
    ui->prog_bar2->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    ui->prog_bar3->setLayout(new QVBoxLayout(ui->prog_bar3));
    ui->prog_bar3->layout()->addWidget(gauge4);
    ui->prog_bar3->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));






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

    QPen pen(Qt::blue);//customize the color of the series in the chart
    pen.setWidth(1);//customize the width of the series in the chart
    series_bigOneChart->setPen(pen);

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

    timer_2 = new QTimer(this);
        connect(timer_2, &QTimer::timeout, this, &MainWindow::advanceSlideshow);
        timer_2->start(3500);


    chart_bigOneChart->setAnimationOptions(QChart::SeriesAnimations);

    QVBoxLayout *layout_bigOneChart = new QVBoxLayout(ui->area_chart);
}


void MainWindow::create_chart(/*final_name, */std::vector<QFrame*> frameArray, int parses){

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



    int parses = std::stoi(preferences_split.at(1));

    QGridLayout *layout = new QGridLayout; //makes the layout be a grid





    // Create and add QFrames to the array
    for(int i = 0; i < parses; i++) {

        QFrame *frame = new QFrame();
        // Set the object name for the QFrame
        frame->setObjectName("frame" + QString::number(++myNamespace2::number_of_frames));
        frameArray.push_back(frame);

        // Create a label and set its text to the current value of number_of_frames
        QLabel *label = new QLabel(QString::number(myNamespace2::number_of_frames), frame);
        label->setAlignment(Qt::AlignCenter);
        label->setFixedSize(frame->size());
        if(flag_first_chart){
            last_counted_frame = frameArray.size()-parses;
            qDebug() << "i  ---- "  << i;
        }
    }

    flag_first_chart = true;


//        for (int i = 0; i < vec_val.size(); i++) {
//            qDebug() << "Pasxa: --> " << vec_val[i];
//        }

    if(parses == 1){
        int mainWidth = this->width();
        int mainHeight = this->height();

        // Create a loading dialog with a spinning animation
        QDialog loadingDialog(this);
        loadingDialog.setModal(true);
        loadingDialog.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        loadingDialog.setStyleSheet("background-color: rgb(0, 0, 0);");
        loadingDialog.setWindowTitle("Loading");
        loadingDialog.setFixedSize(mainWidth, mainHeight);

        QMovie loadingMovie(":/icons/loading-5.gif");
        QLabel loadingLabel(&loadingDialog);
        loadingLabel.setMovie(&loadingMovie);
        loadingMovie.start();

        QVBoxLayout loadingLayout(&loadingDialog);
        loadingLayout.addWidget(&loadingLabel, 0, Qt::AlignCenter);

        // Calculate the position of the loading dialog
        int dialogX = (mainWidth - loadingDialog.width()) / 2;
        int dialogY = (mainHeight - loadingDialog.height()) / 2;

        // Move the loading dialog to the center of the main window
        loadingDialog.move(dialogX, dialogY);

        // Disable the main window
        setDisabled(true);

        // Show the loading dialog
        loadingDialog.show();
        QApplication::processEvents();
        // Run the long-running code
        layout->addWidget(frameArray[frameArray.size()-1], 0, 0);
        std::vector<double> DataRead = Firestore_Read_Data(preferences_split.at(parses+1).c_str());


        QChart *chart = new QChart();
        chart->setTheme(QChart::ChartThemeDark);
        chart->setBackgroundBrush(QBrush(Qt::transparent));
        chart->setTitle(preferences_split.at(parses+1).c_str());
        // Create a QPointF vector and add the values from the array
        QVector<QPointF> points;
        int N = DataRead.size();

//        qDebug() << "AXNEEEEEEE " << dateStr;
        int frontN, rearN;
        bool flagN = false;


        for(int i=0; i<dateOfChartContent.size(); i++)
            std::cout << dateOfChartContent[i] << std::endl;


        QString dateString = QString::fromStdString(dateOfChartContent[dateOfChartContent.size()-1]);
        QStringList parts = dateString.split(" ");
        QString dateStrBreak = parts[0]; // Get the first part (the date)


        for(int i=0; i<dateOfChartContent.size(); i++){
            QString dateString = QString::fromStdString(dateOfChartContent[i]);
            QStringList parts = dateString.split(" ");
            QString dateStr = parts[0]; // Get the first part (the date)
            if(preferences_split.at(parses+2).c_str()==dateStr.toStdString() && flagN==false){
                frontN=i;
                flagN=true;
            }
            if(preferences_split.at(parses+2).c_str()!=dateStr.toStdString() && flagN==true){
                rearN= i-1;
                break;
            }
            if(dateStrBreak.toStdString()==dateStr.toStdString() && flagN==true){
                rearN=dateOfChartContent.size()-1;
                break;
            }
        }

        dateOfChartContent.clear();

        for (int j = frontN; j < rearN; j++) {
                points.append(QPointF(j + 0.5, DataRead[j]));
        }

        // Create a line series with the data points
        QLineSeries *series = new QLineSeries();
        series->append(points);
        chart->addSeries(series);

        // Set up the X-axis with 0.5 increments
        QValueAxis *axisX1 = new QValueAxis();
        axisX1->setTickCount(10);
        axisX1->setLabelFormat("%.1f");
        axisX1->setRange(0, N);
        axisX1->setTickInterval(0.5);
        chart->addAxis(axisX1, Qt::AlignBottom);
        series->attachAxis(axisX1);

        // Set up the Y-axis
        QValueAxis *axisY1 = new QValueAxis();
        chart->addAxis(axisY1, Qt::AlignLeft);
        series->attachAxis(axisY1);

        // Create a chart view object and set the chart
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setChart(chart);

        // Set up the hover area
        // Enable panning and disable zooming
        chartView->setRubberBand(QChartView::HorizontalRubberBand);
        chartView->setDragMode(QGraphicsView::ScrollHandDrag);

        // Disable animations
        chart->setAnimationOptions(QChart::NoAnimation);

        // Get the layout for the current frame and add the chart view
        QVBoxLayout *layout = new QVBoxLayout(frameArray[frameArray.size()-1]);
        layout->addWidget(chartView);

        // Create a label for showing the x and y axis value
        QLabel *label = new QLabel(chartView);
        label->setStyleSheet("QLabel { background-color: #22222; color: white; border: 1px solid white; border-radius: 2px; font-weight: bold; }"); // modify the style sheet to make the labels bold
        label->setGeometry(QRect(0, 0, 120, 40)); // make the label bigger
        label->setVisible(false);
        label->raise(); // set z-index to highest

        // Set the pen of the line series to a thicker width
        QPen pen = series->pen();
        pen.setWidth(3);
        series->setPen(pen);

        // Connect the hovered signal of the series to a custom slot
        QObject::connect(series, &QLineSeries::hovered, [=](const QPointF &point, bool state) {
            if (state) {
                // Show the label and update its text
                label->setVisible(true);
                label->setText(QString("X: %1\nY: %2").arg(point.x()).arg(point.y()));

                // Move the label to the current mouse position
                QPoint mousePos = chartView->mapFromGlobal(QCursor::pos());
                label->move(mousePos.x() - label->width()/2, mousePos.y() - label->height() - 5); // space out the label
            } else {
                // Hide the label
                label->setVisible(false);
            }
        });



        // Hide the loading dialog and enable the main window
        loadingDialog.hide();
        setDisabled(false);

        //sd
    }else if (parses == 2){
        int counter =0;
        int mainWidth = this->width();
        int mainHeight = this->height();

        // Create a loading dialog with a spinning animation
        QDialog loadingDialog(this);
        loadingDialog.setModal(true);
        loadingDialog.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        loadingDialog.setStyleSheet("background-color: rgb(0, 0, 0);");
        loadingDialog.setWindowTitle("Loading");
        loadingDialog.setFixedSize(mainWidth, mainHeight);

        QMovie loadingMovie(":/icons/loading-5.gif");
        QLabel loadingLabel(&loadingDialog);
        loadingLabel.setMovie(&loadingMovie);
        loadingMovie.start();

        QVBoxLayout loadingLayout(&loadingDialog);
        loadingLayout.addWidget(&loadingLabel, 0, Qt::AlignCenter);

        // Calculate the position of the loading dialog
        int dialogX = (mainWidth - loadingDialog.width()) / 2;
        int dialogY = (mainHeight - loadingDialog.height()) / 2;

        // Move the loading dialog to the center of the main window
        loadingDialog.move(dialogX, dialogY);

        // Disable the main window
        setDisabled(true);

        // Show the loading dialog
        loadingDialog.show();
        QApplication::processEvents();
        std::vector<double> DataRead;
        int adder;
        for(int k=last_counted_frame; k<frameArray.size(); k++){
            if(counter == 0) {
                    layout->addWidget(frameArray[k], 0, 0);
                    DataRead = Firestore_Read_Data(preferences_split.at(parses).c_str());
                    adder=0;
                } else {
                    layout->addWidget(frameArray[k], 0, 1);
                    DataRead = Firestore_Read_Data(preferences_split.at(parses+1).c_str());
                    adder=1;
                }


            QChart *chart = new QChart();
            chart->setTheme(QChart::ChartThemeDark);
            chart->setBackgroundBrush(QBrush(Qt::transparent));
            chart->setTitle(preferences_split.at(parses+1).c_str());
            // Create a QPointF vector and add the values from the array
            QVector<QPointF> points;
            int N = DataRead.size();

    //        qDebug() << "AXNEEEEEEE " << dateStr;
            int frontN, rearN;
            bool flagN = false;


            QString dateString = QString::fromStdString(dateOfChartContent[dateOfChartContent.size()-1]);
            QStringList parts = dateString.split(" ");
            QString dateStrBreak = parts[0]; // Get the first part (the date)


            for(int i=0; i<dateOfChartContent.size(); i++){
                QString dateString = QString::fromStdString(dateOfChartContent[i]);
                QStringList parts = dateString.split(" ");
                QString dateStr = parts[0]; // Get the first part (the date)
                if(preferences_split.at(parses+2+adder).c_str()==dateStr.toStdString() && flagN==false){
                    frontN=i;
                    flagN=true;
                }
                std::cout << "EINAI = " << flagN << std::endl;
                std::cout << "EINAI2 = " << dateStr.toStdString() << std::endl;
                std::cout << "EINAI3 = " << dateStrBreak.toStdString() << std::endl;
                if(preferences_split.at(parses+2+adder).c_str()!=dateStr.toStdString() && flagN==true){
                    rearN= i-1;
                    break;
                }
                if(dateStrBreak.toStdString()==dateStr.toStdString() && flagN==true){
                    rearN=dateOfChartContent.size()-1;
                    break;
                }
            }

            dateOfChartContent.clear();

            for (int j = frontN; j < rearN; j++) {
                    points.append(QPointF(j + 0.5, DataRead[j]));
            }

            // Create a line series with the data points
            QLineSeries *series = new QLineSeries();
            series->append(points);
            chart->addSeries(series);

            // Set up the X-axis with 0.5 increments
            QValueAxis *axisX1 = new QValueAxis();
            axisX1->setTickCount(10);
            axisX1->setLabelFormat("%.1f");
            axisX1->setRange(0, N);
            axisX1->setTickInterval(0.5);
            chart->addAxis(axisX1, Qt::AlignBottom);
            series->attachAxis(axisX1);

            // Set up the Y-axis
            QValueAxis *axisY1 = new QValueAxis();
            chart->addAxis(axisY1, Qt::AlignLeft);
            series->attachAxis(axisY1);

            // Create a chart view object and set the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->setChart(chart);

            // Set up the hover area
            // Enable panning and disable zooming
            chartView->setRubberBand(QChartView::HorizontalRubberBand);
            chartView->setDragMode(QGraphicsView::ScrollHandDrag);

            // Disable animations
            chart->setAnimationOptions(QChart::NoAnimation);

            // Get the layout for the current frame and add the chart view
            QVBoxLayout *layout = new QVBoxLayout(frameArray[k]);
            layout->addWidget(chartView);

            // Create a label for showing the x and y axis value
            QLabel *label = new QLabel(chartView);
            label->setStyleSheet("QLabel { background-color: #22222; color: white; border: 1px solid white; border-radius: 2px; font-weight: bold; }"); // modify the style sheet to make the labels bold
            label->setGeometry(QRect(0, 0, 120, 40)); // make the label bigger
            label->setVisible(false);
            label->raise(); // set z-index to highest

            // Set the pen of the line series to a thicker width
            QPen pen = series->pen();
            pen.setWidth(3);
            series->setPen(pen);

            // Connect the hovered signal of the series to a custom slot
            QObject::connect(series, &QLineSeries::hovered, [=](const QPointF &point, bool state) {
                if (state) {
                    // Show the label and update its text
                    label->setVisible(true);
                    label->setText(QString("X: %1\nY: %2").arg(point.x()).arg(point.y()));

                    // Move the label to the current mouse position
                    QPoint mousePos = chartView->mapFromGlobal(QCursor::pos());
                    label->move(mousePos.x() - label->width()/2, mousePos.y() - label->height() - 5); // space out the label
                } else {
                    // Hide the label
                    label->setVisible(false);
                }
            });
            // Hide the loading dialog and enable the main window
                    counter++;
        }
        loadingDialog.hide();
        setDisabled(false);
    }else if(parses == 3){
        int mainWidth = this->width();
        int mainHeight = this->height();

        // Create a loading dialog with a spinning animation
        QDialog loadingDialog(this);
        loadingDialog.setModal(true);
        loadingDialog.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        loadingDialog.setStyleSheet("background-color: rgb(0, 0, 0);");
        loadingDialog.setWindowTitle("Loading");
        loadingDialog.setFixedSize(mainWidth, mainHeight);

        QMovie loadingMovie(":/icons/loading-5.gif");
        QLabel loadingLabel(&loadingDialog);
        loadingLabel.setMovie(&loadingMovie);
        loadingMovie.start();

        QVBoxLayout loadingLayout(&loadingDialog);
        loadingLayout.addWidget(&loadingLabel, 0, Qt::AlignCenter);

        // Calculate the position of the loading dialog
        int dialogX = (mainWidth - loadingDialog.width()) / 2;
        int dialogY = (mainHeight - loadingDialog.height()) / 2;

        // Move the loading dialog to the center of the main window
        loadingDialog.move(dialogX, dialogY);

        // Disable the main window
        setDisabled(true);

        // Show the loading dialog
        loadingDialog.show();
        QApplication::processEvents();
        int counter =0;
        int adder;
        std::vector<double> DataRead;
        for(int i=last_counted_frame; i<frameArray.size(); i++){
            if(counter == 0) {
                    layout->addWidget(frameArray[i], 0, 0);
                    adder=0;
                    DataRead = Firestore_Read_Data(preferences_split.at(parses-1).c_str());
                } else if (counter == 1) {
                    layout->addWidget(frameArray[i], 0, 1);
                    adder=1;
                    DataRead = Firestore_Read_Data(preferences_split.at(parses).c_str());
                }else{
                    layout->addWidget(frameArray[i], 1, 0, 1, 2); //puting the frames like a 2x2 pinaka
                    adder=2;
                    DataRead = Firestore_Read_Data(preferences_split.at(parses+1).c_str());
                }


            QChart *chart = new QChart();
            chart->setTheme(QChart::ChartThemeDark);
            chart->setBackgroundBrush(QBrush(Qt::transparent));
            chart->setTitle(preferences_split.at(parses+1).c_str());
            // Create a QPointF vector and add the values from the array
            QVector<QPointF> points;
            int N = DataRead.size();

    //        qDebug() << "AXNEEEEEEE " << dateStr;
            int frontN, rearN;
            bool flagN = false;


            QString dateString = QString::fromStdString(dateOfChartContent[dateOfChartContent.size()-1]);
            QStringList parts = dateString.split(" ");
            QString dateStrBreak = parts[0]; // Get the first part (the date)


            for(int i=0; i<dateOfChartContent.size(); i++){
                QString dateString = QString::fromStdString(dateOfChartContent[i]);
                QStringList parts = dateString.split(" ");
                QString dateStr = parts[0]; // Get the first part (the date)
                if(preferences_split.at(parses+2+adder).c_str()==dateStr.toStdString() && flagN==false){
                    frontN=i;
                    flagN=true;
                }
                if(preferences_split.at(parses+2+adder).c_str()!=dateStr.toStdString() && flagN==true){
                    rearN= i-1;
                    break;
                }
                if(dateStrBreak.toStdString()==dateStr.toStdString() && flagN==true){
                    rearN=dateOfChartContent.size()-1;
                    break;
                }
            }

            dateOfChartContent.clear();

            for (int j = frontN; j < rearN; j++) {
                    points.append(QPointF(j + 0.5, DataRead[j]));
            }

            // Create a line series with the data points
            QLineSeries *series = new QLineSeries();
            series->append(points);
            chart->addSeries(series);

            // Set up the X-axis with 0.5 increments
            QValueAxis *axisX1 = new QValueAxis();
            axisX1->setTickCount(10);
            axisX1->setLabelFormat("%.1f");
            axisX1->setRange(0, N);
            axisX1->setTickInterval(0.5);
            chart->addAxis(axisX1, Qt::AlignBottom);
            series->attachAxis(axisX1);

            // Set up the Y-axis
            QValueAxis *axisY1 = new QValueAxis();
            chart->addAxis(axisY1, Qt::AlignLeft);
            series->attachAxis(axisY1);

            // Create a chart view object and set the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->setChart(chart);

            // Set up the hover area
            // Enable panning and disable zooming
            chartView->setRubberBand(QChartView::HorizontalRubberBand);
            chartView->setDragMode(QGraphicsView::ScrollHandDrag);

            // Disable animations
            chart->setAnimationOptions(QChart::NoAnimation);

            // Get the layout for the current frame and add the chart view
            QVBoxLayout *layout = new QVBoxLayout(frameArray[i]);
            layout->addWidget(chartView);

            // Create a label for showing the x and y axis value
            QLabel *label = new QLabel(chartView);
            label->setStyleSheet("QLabel { background-color: #22222; color: white; border: 1px solid white; border-radius: 2px; font-weight: bold; }"); // modify the style sheet to make the labels bold
            label->setGeometry(QRect(0, 0, 120, 40)); // make the label bigger
            label->setVisible(false);
            label->raise(); // set z-index to highest

            // Set the pen of the line series to a thicker width
            QPen pen = series->pen();
            pen.setWidth(3);
            series->setPen(pen);

            // Connect the hovered signal of the series to a custom slot
            QObject::connect(series, &QLineSeries::hovered, [=](const QPointF &point, bool state) {
                if (state) {
                    // Show the label and update its text
                    label->setVisible(true);
                    label->setText(QString("X: %1\nY: %2").arg(point.x()).arg(point.y()));

                    // Move the label to the current mouse position
                    QPoint mousePos = chartView->mapFromGlobal(QCursor::pos());
                    label->move(mousePos.x() - label->width()/2, mousePos.y() - label->height() - 5); // space out the label
                } else {
                    // Hide the label
                    label->setVisible(false);
                }
            });
            // Hide the loading dialog and enable the main window
                    counter++;
        }
        loadingDialog.hide();
        setDisabled(false);
    }else if(parses == 4){
        int counter =0;
        int mainWidth = this->width();
        int mainHeight = this->height();

        // Create a loading dialog with a spinning animation
        QDialog loadingDialog(this);
        loadingDialog.setModal(true);
        loadingDialog.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        loadingDialog.setStyleSheet("background-color: rgb(0, 0, 0);");
        loadingDialog.setWindowTitle("Loading");
        loadingDialog.setFixedSize(mainWidth, mainHeight);

        QMovie loadingMovie(":/icons/loading-5.gif");
        QLabel loadingLabel(&loadingDialog);
        loadingLabel.setMovie(&loadingMovie);
        loadingMovie.start();

        QVBoxLayout loadingLayout(&loadingDialog);
        loadingLayout.addWidget(&loadingLabel, 0, Qt::AlignCenter);

        // Calculate the position of the loading dialog
        int dialogX = (mainWidth - loadingDialog.width()) / 2;
        int dialogY = (mainHeight - loadingDialog.height()) / 2;

        // Move the loading dialog to the center of the main window
        loadingDialog.move(dialogX, dialogY);

        // Disable the main window
        setDisabled(true);

        // Show the loading dialog
        loadingDialog.show();
        QApplication::processEvents();
        int adder;
        std::vector<double> DataRead;
        for(int i=last_counted_frame; i<frameArray.size(); i++){
            if(counter == 0) {
                    layout->addWidget(frameArray[i], 0, 0);
                    adder=0;
                    DataRead = Firestore_Read_Data(preferences_split.at(parses-2).c_str());
                }else if(counter == 1) {
                    layout->addWidget(frameArray[i], 0, 1);
                    adder=1;
                    DataRead = Firestore_Read_Data(preferences_split.at(parses-1).c_str());
                }else if(counter == 2){
                    layout->addWidget(frameArray[i], 1, 0); //puting the frames like a 2x2 pinaka
                    adder=2;
                    DataRead = Firestore_Read_Data(preferences_split.at(parses).c_str());
                }else{
                    layout->addWidget(frameArray[i], 1, 1);
                    adder=3;
                    DataRead = Firestore_Read_Data(preferences_split.at(parses+1).c_str());
                }

            QChart *chart = new QChart();
            chart->setTheme(QChart::ChartThemeDark);
            chart->setBackgroundBrush(QBrush(Qt::transparent));
            chart->setTitle(preferences_split.at(parses+1).c_str());
            // Create a QPointF vector and add the values from the array
            QVector<QPointF> points;
            int N = DataRead.size();

    //        qDebug() << "AXNEEEEEEE " << dateStr;
            int frontN, rearN;
            bool flagN = false;


            QString dateString = QString::fromStdString(dateOfChartContent[dateOfChartContent.size()-1]);
            QStringList parts = dateString.split(" ");
            QString dateStrBreak = parts[0]; // Get the first part (the date)


            for(int i=0; i<dateOfChartContent.size(); i++){
                QString dateString = QString::fromStdString(dateOfChartContent[i]);
                QStringList parts = dateString.split(" ");
                QString dateStr = parts[0]; // Get the first part (the date)
                if(preferences_split.at(parses+2+adder).c_str()==dateStr.toStdString() && flagN==false){
                    frontN=i;
                    flagN=true;
                }
                if(preferences_split.at(parses+2+adder).c_str()!=dateStr.toStdString() && flagN==true){
                    rearN= i-1;
                    break;
                }
                if(dateStrBreak.toStdString()==dateStr.toStdString() && flagN==true){
                    rearN=dateOfChartContent.size()-1;
                    break;
                }
            }

            dateOfChartContent.clear();

            for (int j = frontN; j < rearN; j++) {
                    points.append(QPointF(j + 0.5, DataRead[j]));
            }

            // Create a line series with the data points
            QLineSeries *series = new QLineSeries();
            series->append(points);
            chart->addSeries(series);

            // Set up the X-axis with 0.5 increments
            QValueAxis *axisX1 = new QValueAxis();
            axisX1->setTickCount(10);
            axisX1->setLabelFormat("%.1f");
            axisX1->setRange(0, N);
            axisX1->setTickInterval(0.5);
            chart->addAxis(axisX1, Qt::AlignBottom);
            series->attachAxis(axisX1);

            // Set up the Y-axis
            QValueAxis *axisY1 = new QValueAxis();
            chart->addAxis(axisY1, Qt::AlignLeft);
            series->attachAxis(axisY1);

            // Create a chart view object and set the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->setChart(chart);

            // Set up the hover area
            // Enable panning and disable zooming
            chartView->setRubberBand(QChartView::HorizontalRubberBand);
            chartView->setDragMode(QGraphicsView::ScrollHandDrag);

            // Disable animations
            chart->setAnimationOptions(QChart::NoAnimation);

            // Get the layout for the current frame and add the chart view
            QVBoxLayout *layout = new QVBoxLayout(frameArray[i]);
            layout->addWidget(chartView);

            // Create a label for showing the x and y axis value
            QLabel *label = new QLabel(chartView);
            label->setStyleSheet("QLabel { background-color: #22222; color: white; border: 1px solid white; border-radius: 2px; font-weight: bold; }"); // modify the style sheet to make the labels bold
            label->setGeometry(QRect(0, 0, 120, 40)); // make the label bigger
            label->setVisible(false);
            label->raise(); // set z-index to highest

            // Set the pen of the line series to a thicker width
            QPen pen = series->pen();
            pen.setWidth(3);
            series->setPen(pen);

            // Connect the hovered signal of the series to a custom slot
            QObject::connect(series, &QLineSeries::hovered, [=](const QPointF &point, bool state) {
                if (state) {
                    // Show the label and update its text
                    label->setVisible(true);
                    label->setText(QString("X: %1\nY: %2").arg(point.x()).arg(point.y()));

                    // Move the label to the current mouse position
                    QPoint mousePos = chartView->mapFromGlobal(QCursor::pos());
                    label->move(mousePos.x() - label->width()/2, mousePos.y() - label->height() - 5); // space out the label
                } else {
                    // Hide the label
                    label->setVisible(false);
                }
            });

            // Hide the loading dialog and enable the main window
                    counter++;
        }
        loadingDialog.hide();
        setDisabled(false);
    }else{
        qDebug() << "NOPE";
//        for (int i = 0; i < DataRead.size(); i++) {
//            std::cout << "Pasxa: --> " << DataRead[i] << std::endl;
//        }
    }

    QWidget *tabContent = new QWidget; //makes a widget for the tab window

    tabContent->setLayout(layout); //setting the layout of the widget

    QString final_name = QString::fromStdString(preferences_split.at(0));

    //adding a new tab to the TabWidget
    int tabIndex = tabWidget->addTab(tabContent, final_name);

    //setting the name of the new tab
    tabWidget->setTabText(tabIndex, final_name);

}

void MainWindow::chartCreationSetup(int parses, std::vector<std::string> preferences_split, std::vector<QFrame*> frameArray){

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


