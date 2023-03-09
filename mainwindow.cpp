#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qregularexpression.h"
#include "ui_mainwindow.h"
#include "databasehandler1.h"
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
#include <QSemaphore>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <variant>




int vector_counter_chart=0;

bool flag_first_chart=false;
std::vector<QFrame*> frameArray;
int last_counted_frame =0;
std::vector<double> Pasxa;

namespace myNamespace{
    extern float fin_ans,sec_ans,ok;
}

namespace myNamespace2{
    extern int number_of_frames;
//    extern double* array;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
//    DataRead = Firestore_Read_Data("AAA");
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



    if(parses == 1){
        layout->addWidget(frameArray[frameArray.size()-1], 0, 0);
        chartCreationSetup(parses, preferences_split, frameArray);
        std::vector<double> DataRead = Firestore_Read_Data(preferences_split.at(parses+1).c_str());
        qDebug() << "ebala sto frame[" << frameArray.size()-1 << "] = ";
//        for (int i = 0; i < vec_val.size(); i++) {
//            qDebug() << "Pasxa: --> " << vec_val[i];
//        }

        QChart *chart = new QChart();
        chart->setTitle(preferences_split.at(parses+1).c_str());
        // Create a QPointF vector and add the values from the array
        QVector<QPointF> points;
        int N = DataRead.size();
        for (int j = 0; j < N; j++) {
            points.append(QPointF(j + 0.5, DataRead[j]));
        }
        // Create a line series object and set the points
        QLineSeries *series = new QLineSeries();
        series->append(points);
        chart->addSeries(series);

        // Set up the X-axis with 0.5 increments
        QValueAxis *axisX1 = new QValueAxis();
        axisX1->setTickCount(N);
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

        // Get the layout for the current frame and add the chart view
        QVBoxLayout *layout = new QVBoxLayout(frameArray[frameArray.size()-1]);
        layout->addWidget(chartView);


    }else if (parses == 2){
        int counter =0;
        for(int i=last_counted_frame; i<frameArray.size(); i++){
            if(counter == 0) {
                    layout->addWidget(frameArray[i], 0, 0);
                } else {
                    layout->addWidget(frameArray[i], 0, 1);
                }

                std::vector<double> DataRead = Firestore_Read_Data(preferences_split.at(counter + 2).c_str());
                qDebug() << "ebala sto frame[" << i << "] = ";

                QChart *chart = new QChart();
                chart->setTitle(preferences_split.at(counter + 2).c_str());

                // Create a line series object and set the points
                QLineSeries *series = new QLineSeries();

                // Create a QPointF vector and add the values from the array
                QVector<QPointF> points;
                int N = DataRead.size();
                for (int j = 0; j < N; j++) {
                    points.append(QPointF(j + 0.5, DataRead[j]));
                }

                series->append(points);
                chart->addSeries(series);

                // Set up the X-axis with 0.5 increments
                QValueAxis *axisX1 = new QValueAxis();
                axisX1->setTickCount(N);
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

                // Get the layout for the current frame and add the chart view
                QVBoxLayout *layout = new QVBoxLayout(frameArray[i]);
                layout->addWidget(chartView);

                counter++;
        }
    }else if(parses == 3){

        int counter =0;
        for(int i=last_counted_frame; i<frameArray.size(); i++){
            if(counter == 0) {
                    layout->addWidget(frameArray[i], 0, 0);
                } else if (counter == 1) {
                    layout->addWidget(frameArray[i], 0, 1);
                }else{
                    layout->addWidget(frameArray[i], 1, 0, 1, 2); //puting the frames like a 2x2 pinaka
                }

                std::vector<double> DataRead = Firestore_Read_Data(preferences_split.at(counter + 2).c_str());
                qDebug() << "ebala sto frame[" << i << "] = ";

                QChart *chart = new QChart();
                chart->setTitle(preferences_split.at(counter + 2).c_str());

                // Create a line series object and set the points
                QLineSeries *series = new QLineSeries();

                // Create a QPointF vector and add the values from the array
                QVector<QPointF> points;
                int N = DataRead.size();
                for (int j = 0; j < N; j++) {
                    points.append(QPointF(j + 0.5, DataRead[j]));
                }

                series->append(points);
                chart->addSeries(series);

                // Set up the X-axis with 0.5 increments
                QValueAxis *axisX1 = new QValueAxis();
                axisX1->setTickCount(N);
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

                // Get the layout for the current frame and add the chart view
                QVBoxLayout *layout = new QVBoxLayout(frameArray[i]);
                layout->addWidget(chartView);

                counter++;
        }
    }else if(parses == 4){
        int counter =0;
        for(int i=last_counted_frame; i<frameArray.size(); i++){
            if(counter == 0) {
                    layout->addWidget(frameArray[i], 0, 0);
                }else if(counter == 1) {
                    layout->addWidget(frameArray[i], 0, 1);
                }else if(counter == 2){
                    layout->addWidget(frameArray[i], 1, 0); //puting the frames like a 2x2 pinaka
                }else{
                    layout->addWidget(frameArray[i], 1, 1);
                }

                std::vector<double> DataRead = Firestore_Read_Data(preferences_split.at(counter + 2).c_str());
                qDebug() << "ebala sto frame[" << i << "] = ";

                QChart *chart = new QChart();
                chart->setTitle(preferences_split.at(counter + 2).c_str());

                // Create a line series object and set the points
                QLineSeries *series = new QLineSeries();

                // Create a QPointF vector and add the values from the array
                QVector<QPointF> points;
                int N = DataRead.size();
                for (int j = 0; j < N; j++) {
                    points.append(QPointF(j + 0.5, DataRead[j]));
                }

                series->append(points);
                chart->addSeries(series);


                // Set up the X-axis with 0.5 increments
                QValueAxis *axisX1 = new QValueAxis();
                axisX1->setTickCount(N);
                axisX1->setLabelFormat("%.1f");
                axisX1->setRange(0, 2);
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
                chartView->setDragMode(QGraphicsView::ScrollHandDrag); // Enable drag mode

                // Get the layout for the current frame and add the chart view
                QVBoxLayout *layout = new QVBoxLayout(frameArray[i]);
                layout->addWidget(chartView);

                counter++;
        }
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




