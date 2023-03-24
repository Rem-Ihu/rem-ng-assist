#include "mainwindow.h"
//#include "login_sign_up_in.h"
#include "./ui_mainwindow.h"
#include "qregularexpression.h"
#include <QJSEngine>
#include <QDebug>
#include "ui_mainwindow.h"
#include "databasehandler1.h"
#include <QSvgRenderer>
#include <QStackedWidget>
#include <QDialog>
#include <iostream>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <sstream>
#include <QSvgRenderer>
#include <QPixmap>
#include <QCalendarWidget>
#include <QVBoxLayout>
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




int vector_counter_chart=0;
bool flag_first_chart=false;
std::vector<QFrame*> frameArray;
int last_counted_frame =0;
std::vector<double> Pasxa;
#include <sstream>


namespace myNamespace{
    extern float fin_ans,sec_ans,ok;
}

namespace myNamespace2{
    extern int number_of_frames;
//    extern double* array;
}

namespace username_change{
    extern int pass_check_number;
    extern std::vector<std::string> full_name;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{




    // set font to bold, doesnt work to text browsers
   //QFont font;
    //font.setWeight(QFont::Bold);
    // Set the default font for all widgets to be bold
   //QApplication::setFont(font);
    ui->setupUi(this);
    ui->resolutionslider->setValue(25);




    QCalendarWidget *calendar = new QCalendarWidget(this);

    // Set the text format for the current date with the text "My Text"
    QTextCharFormat format1212;
    format1212.setForeground(Qt::red);
    calendar->setDateTextFormat(QDate::currentDate(), format1212);

    // Define date and color array
    QDate dates[] = { QDate(2023, 3, 3), QDate(2023, 3, 15), QDate(2023, 3, 28), QDate(2023, 3, 31), QDate(2023, 10, 2), QDate(2023, 10, 2), QDate(2023, 6, 9), QDate(2023, 5, 1)};
    QColor colors[] = { QColor(48, 172, 255), QColor(255, 125, 33), QColor(161, 66, 255), QColor(152, 8, 8), QColor(12, 207, 100) };

    // Loop over dates and set text format for each one
    for (int i = 0; i < 5; i++) {
        QTextCharFormat format1;
        format1.setBackground(QBrush(colors[i]));
        calendar->setDateTextFormat(dates[i], format1);
    }

    // Set stylesheet to remove arrows and make the month and year background transparent
    calendar->setStyleSheet("QCalendarWidget QAbstractItemView {"
                            "selection-background-color: palette(highlight);"
                            "selection-color: palette(highlighted-text);"
                            "background-color: transparent; }"
                            "QCalendarWidget QWidget {"
                            "background-color: transparent; }"
                            "QCalendarWidget QToolButton {"
                            "background-color: transparent; }"
                            "QCalendarWidget QToolButton#qt_calendar_prevmonth {"
                            "icon-size: 0px; }"
                            "QCalendarWidget QToolButton#qt_calendar_nextmonth {"
                            "icon-size: 0px; }");

    // Add calendar widget to layout
    QVBoxLayout *layout = new QVBoxLayout(ui->frameCalendar);
    layout->addWidget(calendar);
    ui->frameCalendar->setLayout(layout);










    class RadialThermometerProgressBar : public QProgressBar {
    public:
        RadialThermometerProgressBar(QWidget* parent = nullptr) : QProgressBar(parent) {
            setFixedSize(190, 190);
        }

    protected:
        void paintEvent(QPaintEvent* event) override {
            Q_UNUSED(event);
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing, true);

            QRectF rect = this->rect().adjusted(20, 20, -20, -30);
            int minSize = qMin(rect.width(), rect.height());
            int padding = qMax(minSize / 50, 4);
            int fontSize = qMax(minSize / 40, 20);

            QFont font;
            font.setPointSize(fontSize);
            painter.setFont(font);

            // Draw the background circle
            painter.setPen(QPen(QBrush(QColor(Qt::transparent)), padding));
            painter.setBrush(Qt::NoBrush);
            painter.drawEllipse(rect);

            // Draw the progress arc
            painter.setPen(QPen(QBrush(Qt::cyan), padding * 2));
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
    RadialThermometerProgressBar* gauge1 = new RadialThermometerProgressBar(ui->progressBarLeft);
    RadialThermometerProgressBar* gauge2 = new RadialThermometerProgressBar(ui->progressBarMiddle);
    RadialThermometerProgressBar* gauge3 = new RadialThermometerProgressBar(ui->progressBarRight);

    // Set progress bar ranges and values
    gauge1->setRange(0, 100);
    gauge1->setValue(25);

    gauge2->setRange(0, 100);
    gauge2->setValue(50);

    gauge3->setRange(0, 100);
    gauge3->setValue(75);

    ui->progressBarLeft->setLayout(new QVBoxLayout(ui->progressBarLeft));
    ui->progressBarLeft->layout()->addWidget(gauge1);
    ui->progressBarLeft->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    ui->progressBarMiddle->setLayout(new QVBoxLayout(ui->progressBarMiddle));
    ui->progressBarMiddle->layout()->addWidget(gauge2);
    ui->progressBarMiddle->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

    ui->progressBarRight->setLayout(new QVBoxLayout(ui->progressBarRight));
    ui->progressBarRight->layout()->addWidget(gauge3);
    ui->progressBarRight->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));


    QTimer *timer_2 = new QTimer(this);
        connect(timer_2, &QTimer::timeout, this, &MainWindow::advanceSlideshow);
        timer_2->start(3500);



    //REAL TIME CHART SETUP
    QSplineSeries *series_bigOneChart = new QSplineSeries();//create the series for the aero chart
    series_bigOneChart->setName("Real Time Values");//set the name of the measurement


    QString username = QString::fromStdString(username_change::full_name[username_change::pass_check_number]);
    ui->username_label->setText(username);


    QChart *chart_bigOneChart = new QChart();//create the aero chart
    chart_bigOneChart->addSeries(series_bigOneChart); //add the values
    QFont titleFont("Arial", 16, QFont::Bold); // Create a QFont object with desired font family, size, and weight
    chart_bigOneChart->setTitle("Real Time Chart"); // Set the chart title
    chart_bigOneChart->setTitleFont(titleFont); // Set the font of the chart title
    chart_bigOneChart->createDefaultAxes(); //create the axes
    chart_bigOneChart->axes(Qt::Vertical).first()->setRange(-7, 130); //set the range of values of axis y
    chart_bigOneChart->setTitleBrush(QBrush(Qt::white));//customize the color of the title in the chart
    chart_bigOneChart->setBackgroundBrush(QBrush(Qt::transparent));//customize the color of the background in the chart



    // Create a QTimer object and set its interval to 500 milliseconds (0.5 seconds)
    QTimer *timer = new QTimer(this); //create a timer
    timer->setInterval(150); //to 80 milliseconds

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
        if(myNamespace::fin_ans!=0 && myNamespace::sec_ans!=0){
            series_bigOneChart->append(x, y);
            x++;
        }
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

    chart_bigOneChart->setTheme(QChart::ChartThemeDark);
    chart_bigOneChart->setBackgroundBrush(Qt::transparent);

    QColor orange(255, 165, 0); // RGB values for orange
    QPen pen(orange);//customize the color of the series in the chart--create the color layer
    pen.setWidth(5);//customize the width of the series in the chart
    series_bigOneChart->setPen(pen); //apply the color to the series
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




    // Create a label for showing the x and y axis value
    QLabel *label = new QLabel(chartView_bigOneChart);
    label->setStyleSheet("QLabel { background-color: #22222; color: white; border: 1px solid white; border-radius: 2px; font-weight: bold; }"); // modify the style sheet to make the labels bold
    label->setGeometry(QRect(0, 0, 120, 40)); // make the label bigger
    label->setVisible(true); // Set the label to be visible by default
    label->raise(); // set z-index to highest

    // Create a label for showing the plot points
    QLabel *pointLabel = new QLabel(chartView_bigOneChart);
    pointLabel->setStyleSheet("QLabel { background-color: #22222; color: white; border: 1px solid white; border-radius: 2px; font-weight: bold; }"); // modify the style sheet to make the labels bold
    pointLabel->setGeometry(QRect(0, 0, 120, 40)); // make the label bigger
    pointLabel->setVisible(true); // Set the label to be visible by default
    pointLabel->raise(); // set z-index to highest

    // Connect the signal of the chart view to a custom slot
    QObject::connect(chartView_bigOneChart, &QChartView::rubberBandChanged, [=](const QRectF &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint) {
        QPointF point = chartView_bigOneChart->chart()->mapToValue(chartView_bigOneChart->mapToScene(toScenePoint.toPoint()));
        // Update the label with the new x and y values
        label->setText(QString("X: %1\nY: %2").arg(point.x()).arg(point.y()));
    });

    // Connect the clicked signal of the series to a custom slot
    QObject::connect(series_bigOneChart, &QLineSeries::clicked, [=](const QPointF &point) {
        // Update the point label text and position
        pointLabel->setText(QString("Point: (%1, %2)").arg(point.x()).arg(point.y()));
        pointLabel->move(chartView_bigOneChart->width() - pointLabel->width() - 5, chartView_bigOneChart->height() - pointLabel->height() - 5);
    });

    // Connect the series signal to update the label as x value changes
    QObject::connect(series_bigOneChart, &QLineSeries::pointAdded, [=](int index) {
        // Get the latest x value
        qreal x = series_bigOneChart->at(index).x();
        // Update the label text
        label->setText(QString("X: %1\nY: %2").arg(x).arg(series_bigOneChart->at(index).y()));
    });

    // Add the chart view, label, and point label to the layout
    QVBoxLayout *layout_bigOneChart1 = new QVBoxLayout(ui->bigOneChart_2);
    layout_bigOneChart1->addWidget(chartView_bigOneChart);
    layout_bigOneChart1->addWidget(label);
    layout_bigOneChart1->addWidget(pointLabel);
//    qDebug() << series_bigOneChart;


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



void MainWindow::create_chart(/*final_name, */std::vector<QFrame*> frameArray, int parses){

//        qDebug() << "HEREEEEE--->" << frameArray.size();

    qDebug() << "HEREEEEE VECTOR--->" << vector_counter_chart;
//    qDebug() << "HEREEEEE N--->" << N;

//    for (int i = 0; i < frameArray.size(); i++) {
//        QChart *chart = new QChart();
//        chart->setTitle("My Chart " + QString::number(i+1));
//        // Create a QPointF vector and add the values from the array
//        QVector<QPointF> points;
//        for (int j = vector_counter_chart; j < myNamespace2::N; j++) {
//            points.append(QPointF(j + 0.5, myNamespace2::array[j]));
//        }

//        // Create a line series object and set the points
//        QLineSeries *series = new QLineSeries();
//        series->append(points);
//        chart->addSeries(series);

//        // Set up the X-axis with 0.5 increments
//        QValueAxis *axisX1 = new QValueAxis();
//        axisX1->setTickCount(myNamespace2::N);
//        axisX1->setLabelFormat("%.1f");
//        axisX1->setRange(0, myNamespace2::N);
//        axisX1->setTickInterval(0.5);
//        chart->addAxis(axisX1, Qt::AlignBottom);
//        series->attachAxis(axisX1);

//        // Set up the Y-axis
//        QValueAxis *axisY1 = new QValueAxis();
//        chart->addAxis(axisY1, Qt::AlignLeft);
//        series->attachAxis(axisY1);

//        // Create a chart view object and set the chart
//        QChartView *chartView = new QChartView(chart);
//        chartView->setRenderHint(QPainter::Antialiasing);
//        chartView->setChart(chart);

//        // Get the layout for the current frame and add the chart view
//        QVBoxLayout *layout = new QVBoxLayout(frameArray[i]);
//        layout->addWidget(chartView);
//    }


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

void MainWindow::on_pushButtonAboutUs_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_pushButtonContact_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}


void MainWindow::on_pushButtonHome_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
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








void MainWindow::on_displaybutton_clicked()
{
    ui->optionswidget->setCurrentIndex(0);
}


void MainWindow::on_historybutton_clicked()
{
    ui->optionswidget->setCurrentIndex(1);
}


void MainWindow::on_measurementsbutton_clicked()
{
    ui->optionswidget->setCurrentIndex(2);
}


void MainWindow::on_accountbutton_clicked()
{
    ui->optionswidget->setCurrentIndex(3);
}

void MainWindow::on_greenblack_clicked()
{
    ui->centralwidget->setStyleSheet("background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0.1 black, stop:0.95 #1E8449)");
}


void MainWindow::on_defaultblackblue_clicked()
{
 ui->centralwidget->setStyleSheet("background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0.1 black, stop:0.95 #0C2A6A)");
}


void MainWindow::on_bluepink_clicked()
{
    ui->centralwidget->setStyleSheet( "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0.1 black, stop:0.95 #17AEBF)");
}


void MainWindow::on_whiteblack_clicked()
{
     ui->centralwidget->setStyleSheet( "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0.05 black, stop:0.95 white)");
}


void MainWindow::on_blackpurple_clicked()
{
  ui->centralwidget->setStyleSheet("background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0.1 black, stop:0.95 #8B00FF)");
;
}


void MainWindow::on_blackred_clicked()
{
    ui->centralwidget->setStyleSheet(" background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0.1 black, stop:0.95 #8B0000)");
}


void MainWindow::on_resolutionslider_valueChanged(int value)
{

    QScreen *screen = QGuiApplication::primaryScreen();
    QWindow *window = windowHandle();
    if (screen && window) {
        int width = screen->size().width() * value  / 100;
        int height = screen->size().height() * value  / 100;
        QPoint pos = window->position();
        window->setGeometry(pos.x(), pos.y(), width, height);

        // Update the slider value
        ui->resolutionslider->blockSignals(true);
        ui->resolutionslider->setValue(value);
        ui->resolutionslider->blockSignals(false);
    }
    }



void MainWindow::on_chart1buttonhistory_clicked()
{
     ui->historystacked->setCurrentIndex(0);
}


void MainWindow::on_chart2buttonhistory_clicked()
{
    ui->historystacked->setCurrentIndex(1);
}


void MainWindow::on_chart3buttonhistory_clicked()
{
    ui->historystacked->setCurrentIndex(2);
}


void MainWindow::on_chart4buttonhistory_clicked()
{
    ui->historystacked->setCurrentIndex(3);
}


void MainWindow::on_chart5buttonhistory_clicked()
{
    ui->historystacked->setCurrentIndex(4);
}


void MainWindow::on_chart6buttonhistory_clicked()
{
    ui->historystacked->setCurrentIndex(5);
}


void MainWindow::on_chart7buttonhistory_clicked()
{
    ui->historystacked->setCurrentIndex(6);
}

void MainWindow::on_IconButton_clicked()
{
    {
        // Show a file dialog to select a new icon file
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png *.xpm *.jpg)"));

        if (!fileName.isEmpty())
        {
            // Set the style sheet of the button to change its icon to the selected image
            QString styleSheet = QString("QPushButton#IconButton { border-image: url(%1); }").arg(fileName);
            ui->IconButton->setStyleSheet(styleSheet);

            // Update the icon of the button to reflect the selected image
           ui->IconButton->setIcon(QIcon(fileName));
        }

    }
}



void MainWindow::on_password_button_clicked()
{
    QUrl url("mailto:team@remihu.eu?Body=Greetings%20REM%20team%0AI%27d%20like%20to%20request%20a%20password%20change%20in%20the%20official%20REM%20app.%0AThanks%20in%20advance.");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_username_button_clicked()
{
    QUrl url("mailto:team@remihu.eu?Body=Greetings%20REM%20team%0AI%27d%20like%20to%20request%20a%20username%20change%20in%20the%20official%20REM%20app.%0AThanks%20in%20advance.");
    QDesktopServices::openUrl(url);
        }


void MainWindow::on_go_back_user_clicked()
{
    ui->accountstack->setCurrentIndex(0);
}


void MainWindow::on_go_back_passw_clicked()
{
    ui->accountstack->setCurrentIndex(0);
}


void MainWindow::on_color_change_button_clicked()
{
    QColor color = QColorDialog::getColor();
        if (color.isValid())
        {
            QString styleSheet = QString("background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0.1 black, stop:0.95 %1) }").arg(color.name());
            ui->centralwidget->setStyleSheet(styleSheet);
        }
   }




void MainWindow::on_pushButtonLogOut_clicked()
{

}


void MainWindow::on_web_button_clicked()
{

        QUrl url("https://remihu.eu/");
        QDesktopServices::openUrl(url);
}


void MainWindow::on_sponsors_button_clicked()
{
    QUrl url("https://remihu.eu/sponsors/2021-23/");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_email_button_clicked()
{
    QUrl url("mailto:team@remihu.eu");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_map2_clicked()
{
    QUrl url("https://www.google.com/maps/place/%CE%94%CE%B9%CE%B5%CE%B8%CE%BD%CE%AD%CF%82+%CE%A0%CE%B1%CE%BD%CE%B5%CF%80%CE%B9%CF%83%CF%84%CE%AE%CE%BC%CE%B9%CE%BF+%CF%84%CE%B7%CF%82+%CE%95%CE%BB%CE%BB%CE%AC%CE%B4%CE%BF%CF%82+%CF%80%CE%B1%CE%BD%CE%B5%CF%80%CE%B9%CF%83%CF%84%CE%B7%CE%BC%CE%B9%CE%BF%CF%8D%CF%80%CE%BF%CE%BB%CE%B7+%CE%A3%CE%B5%CF%81%CF%81%CF%8E%CE%BD/@41.0751444,23.5484963,16.48z/data=!4m10!1m2!2m1!1sdipae+serres!3m6!1s0x14a9718e43956661:0x3c635d9f4c5c8a1a!8m2!3d41.0747983!4d23.5537024!15sCgxkaXBhZSBzZXJyZXNaDiIMZGlwYWUgc2VycmVzkgERcHVibGljX3VuaXZlcnNpdHngAQA!16s%2Fm%2F0qsc8x5");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_map1_clicked()
{
    QUrl url("https://www.google.com/maps/place/%CE%94%CE%B9%CE%B5%CE%B8%CE%BD%CE%AD%CF%82+%CE%A0%CE%B1%CE%BD%CE%B5%CF%80%CE%B9%CF%83%CF%84%CE%AE%CE%BC%CE%B9%CE%BF+%CF%84%CE%B7%CF%82+%CE%95%CE%BB%CE%BB%CE%AC%CE%B4%CE%BF%CF%82+%CF%80%CE%B1%CE%BD%CE%B5%CF%80%CE%B9%CF%83%CF%84%CE%B7%CE%BC%CE%B9%CE%BF%CF%8D%CF%80%CE%BF%CE%BB%CE%B7+%CE%A3%CE%B5%CF%81%CF%81%CF%8E%CE%BD/@41.0751444,23.5484963,16.48z/data=!4m10!1m2!2m1!1sdipae+serres!3m6!1s0x14a9718e43956661:0x3c635d9f4c5c8a1a!8m2!3d41.0747983!4d23.5537024!15sCgxkaXBhZSBzZXJyZXNaDiIMZGlwYWUgc2VycmVzkgERcHVibGljX3VuaXZlcnNpdHngAQA!16s%2Fm%2F0qsc8x5");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_facebook_button_clicked()
{
    QUrl url("https://www.facebook.com/ridethethunder");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_insta_button_clicked()
{
    QUrl url("https://www.instagram.com/rem.ihu/");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_tiktok_button_clicked()
{
    QUrl url("https://www.tiktok.com/@rem.ihu?_t=8apyi27wnn4&_r=1");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_tribute_link_clicked()
{
    QUrl url("https://remihu.eu/02-11-2022_a-tribute-to-our-sponsors/");
    QDesktopServices::openUrl(url);
}



void MainWindow::on_bmwxihu_link_clicked()
{
    QUrl url("https://remihu.eu/07-11-2022_rem-ihu-x-bmw-motorrad-hellas/");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_abbxihu_link_clicked()
{
    QUrl url("https://remihu.eu/16-11-2022_rem-ihu-x-abb/");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_remxsp_clicked()
{
    QUrl url("https://remihu.eu/25-11-2022_rem-ihu-x-sp-motorsports/");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_remxtypo_clicked()
{
    QUrl url("https://remihu.eu/23-11-2022_rem-ihu-x-typographic/");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_bmu_link_clicked()
{
    QUrl url("https://remihu.eu/24-10-2022_bmu-championship/");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_challenge_link_clicked()
{
    QUrl url("https://remihu.eu/31-03-2022_pressentation-challenge-of-march-2022/");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_presentation_link_clicked()
{
    QUrl url("https://remihu.eu/29-05-2022_presentation-with-bmw-motorrad-hellas/");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_serres_racing_link_clicked()
{
    QUrl url("https://remihu.eu/23-06-2022_support-from-serres-racing-circuit/");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_adaylink_clicked()
{
    QUrl url("https://remihu.eu/05-06-2022_a-day-to-be-remembered/");
    QDesktopServices::openUrl(url);
}

