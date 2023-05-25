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
//#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QFrame>
#include <QtMultimedia/QCamera>



int vector_counter_chart=0;
bool flag_first_chart=false;
std::vector<QFrame*> frameArray;
int last_counted_frame =0;
std::vector<double> Pasxa;
std::vector<int> tries;
#include <sstream>
//test ui


namespace myNamespace{
    extern float first_realtime_answer,second_realtime_answer,ok;
}

namespace myNamespace2{
    extern int number_of_frames;
}

namespace username_change{
    extern int pass_check_number;
    extern std::vector<std::string> full_name;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{

    ui->setupUi(this);
    ui->resolutionslider->setValue(25);


//    QFrame *VIDEO_frame = findChild<QFrame*>("realtimevideo");

//    VIDEO_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    QVBoxLayout *VIDEO_layout = new QVBoxLayout(VIDEO_frame);

//    QWebEngineView *VIDEO_view = new QWebEngineView(VIDEO_frame);
//    VIDEO_view->setUrl(QUrl("https://stream.remihu.eu/")); //our url
//    VIDEO_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    VIDEO_layout->addWidget(VIDEO_view);





    QCalendarWidget *calendar = new QCalendarWidget(this); // Setting up the calendar


    QTextCharFormat format1212; // Set the text format for the current date with the text "My Text"
    format1212.setForeground(Qt::red);
    calendar->setDateTextFormat(QDate::currentDate(), format1212);

    // Define date and color array
    QDate dates[] = { QDate(2023, 3, 3), QDate(2023, 3, 15), QDate(2023, 3, 28), QDate(2023, 3, 31), QDate(2023, 10, 2), QDate(2023, 10, 2), QDate(2023, 6, 9), QDate(2023, 5, 1)};
    QColor colors[] = { QColor(48, 172, 255), QColor(255, 125, 33), QColor(161, 66, 255), QColor(152, 8, 8), QColor(12, 207, 100) };


    for (int i = 0; i < 5; i++) { // Loop over dates and set text format for each one
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


    QVBoxLayout *calendar_layout = new QVBoxLayout(ui->frameCalendar); // Add calendar widget to layout
    calendar_layout->addWidget(calendar);
    ui->frameCalendar->setLayout(calendar_layout);









    //GAUGE CLASS
    class RadialThermometerProgressBar : public QProgressBar {
    public:
        RadialThermometerProgressBar(QWidget* parent = nullptr) : QProgressBar(parent) {
            setFixedSize(190, 190);
        }

    protected:
        void paintEvent(QPaintEvent* event) override { // Define a function to handle painting events for the widget
            Q_UNUSED(event); // Indicate that the `event` parameter is not used to avoid a compiler warning
            QPainter painter(this); // Create a QPainter object to draw on the widget
            painter.setRenderHint(QPainter::Antialiasing, true); // Set a rendering hint to enable antialiasing

            QRectF rect = this->rect().adjusted(20, 20, -20, -30); // Create a rectangle to define the drawing area, adjusted with a margin
            int minSize = qMin(rect.width(), rect.height()); // Determine the smaller dimension of the rectangle and calculate padding and font size based on that size
            int padding = qMax(minSize / 50, 4);
            int fontSize = qMax(minSize / 40, 20);

            QFont font; // Create a font object and set the point size
            font.setPointSize(fontSize);
            painter.setFont(font);

            // Draw the background circle
            painter.setPen(QPen(QBrush(QColor(Qt::transparent)), padding)); // Set the pen color and thickness
            painter.setBrush(Qt::NoBrush); // Set the fill color to none
            painter.drawEllipse(rect); // Draw the ellipse

            // Draw the progress arc
            painter.setPen(QPen(QBrush(Qt::cyan), padding * 2)); // Set the pen color and thickness
            painter.setBrush(Qt::NoBrush); // Set the fill color to none
            int value = this->value(); // Get the current value of the widget
            if (value > minimum() && value < maximum()) { // Only draw the arc if the value is within the minimum and maximum range
                int angle = (int)((value - minimum()) * 180.0 / (maximum() - minimum())); // Calculate the angle of the arc based on the value
                painter.drawArc(rect, 180 * 16, -angle * 16); // Draw the arc
            }

            // Draw the value text
            painter.setPen(QPen(QBrush(Qt::white), padding)); // Set the pen color and thickness
            painter.setBrush(Qt::NoBrush); // Set the fill color to none
            QString valueStr = QString::number(value); // Convert the value to a string
            QRect valueRect = painter.fontMetrics().boundingRect(valueStr); // Get the bounding rectangle of the text
            painter.drawText(rect.center() - valueRect.center(), valueStr); // Draw the text centered within the widget

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

    ui->progressBarLeft->setLayout(new QVBoxLayout(ui->progressBarLeft)); // Set the layout of progressBarLeft to a new QVBoxLayout
    ui->progressBarLeft->layout()->addWidget(gauge1); // Add gauge1 widget to the layout of progressBarLeft
    ui->progressBarLeft->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding)); // Add a new QSpacerItem to the layout of progressBarLeft to expand the space

    ui->progressBarMiddle->setLayout(new QVBoxLayout(ui->progressBarMiddle)); // Set the layout of progressBarMiddle to a new QVBoxLayout
    ui->progressBarMiddle->layout()->addWidget(gauge2); // Add gauge2 widget to the layout of progressBarMiddle
    ui->progressBarMiddle->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding)); // Add a new QSpacerItem to the layout of progressBarMiddle to expand the space

    ui->progressBarRight->setLayout(new QVBoxLayout(ui->progressBarRight)); // Set the layout of progressBarRight to a new QVBoxLayout
    ui->progressBarRight->layout()->addWidget(gauge3); // Add gauge3 widget to the layout of progressBarRight
    ui->progressBarRight->layout()->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding)); // Add a new QSpacerItem to the layout of progressBarRight to expand the space


    QTimer *advanceSlideshow_timer = new QTimer(this);
        connect(advanceSlideshow_timer, &QTimer::timeout, this, &MainWindow::advanceSlideshow);
        advanceSlideshow_timer->start(3500);



    //REAL TIME CHART SETUP
    QSplineSeries *realtime_series = new QSplineSeries(); // Create the series for the aero chart
    realtime_series->setName("Real Time Values"); // Set the name of the measurement


    QString username = QString::fromStdString(username_change::full_name[username_change::pass_check_number]);
    ui->username_label->setText(username);


    QChart *realtime_chart = new QChart(); //Create the aero chart
    realtime_chart->addSeries(realtime_series); // Add the values
    QFont titleFont("Arial", 16, QFont::Bold); // Create a QFont object with desired font family, size, and weight
    realtime_chart->setTitle("Real Time Chart"); // Set the chart title
    realtime_chart->setTitleFont(titleFont); // Set the font of the chart title
    realtime_chart->createDefaultAxes(); // Create the axes
    realtime_chart->axes(Qt::Vertical).first()->setRange(-7, 130); // Set the range of values of axis y
    realtime_chart->setTitleBrush(QBrush(Qt::white)); // Customize the color of the title in the chart
    realtime_chart->setBackgroundBrush(QBrush(Qt::transparent)); // Customize the color of the background in the chart



    // Create a QTimer object and set its interval to 150 milliseconds (0.5 seconds)
    QTimer *realtime_chart_timer = new QTimer(this); //create a timer
    realtime_chart_timer->setInterval(150); //to 150 milliseconds

    int x = 0;

    // Add the first 10 data points
    for (int i = 0; i < 10; i++) {
        float y = myNamespace::second_realtime_answer;
        realtime_series->append(x, y);
        x++;
    }
    connect(realtime_chart_timer, &QTimer::timeout, [=]() mutable {  // Connect the timeout() signal of the timer to a lambda function that generates random numbers and updates the chart
        float y = myNamespace::second_realtime_answer;

        // Append the new data point
        QTime currentTime = QTime::currentTime();
        QString currentTimeString = currentTime.toString("hh:mm:ss");
        if(myNamespace::first_realtime_answer!=0 && myNamespace::second_realtime_answer!=0){
            realtime_series->append(x, y);
            x++;
        }
        // Remove the first data point if the series has more than 20 points
        if (realtime_series->count() > 20) {
            realtime_series->remove(0);
        }

        // Update the X range of the chart to show the last 20 data points
        realtime_chart->setAnimationOptions(QChart::NoAnimation);
        realtime_chart->axes(Qt::Horizontal).first()->setRange(x - 20, x);
    });

    // Start the timer
    realtime_chart_timer->start();



    realtime_chart->setPlotAreaBackgroundBrush(QColor(255, 255, 255, 0)); // Set the color of the plot area to trasnparent
    realtime_chart->setPlotAreaBackgroundVisible(true); // Set the application layer to visible
    realtime_chart->setAnimationOptions(QChart::NoAnimation); // Disable the animation for a smoother transition from point to point
    realtime_chart->setTheme(QChart::ChartThemeDark); // Change the theme of the chart
    realtime_chart->setBackgroundBrush(Qt::transparent); // Apply transparent to the background

    QColor orange(255, 165, 0); // RGB values for orange
    QPen pen(orange); // Customize the color of the series in the chart--create the color layer
    pen.setWidth(5); // Customize the width of the series in the chart
    realtime_series->setPen(pen); // Apply the color to the series
    QFrame *frame = ui->realtime_chart_frame; // Place the chart on the frame

    QChartView *realtime_chartView = new QChartView(realtime_chart);
    realtime_chartView->setRenderHint(QPainter::Antialiasing);
    realtime_chartView->setBackgroundBrush(QBrush());




    // Create a label for showing the x and y axis value
    QLabel *plot_points_label = new QLabel(realtime_chartView);
    plot_points_label->setStyleSheet("QLabel { background-color: #22222; color: white; border: 1px solid white; border-radius: 2px; font-weight: bold; }"); // Modify the style sheet to make the labels bold
    plot_points_label->setGeometry(QRect(0, 0, 120, 40)); // Make the label bigger
    plot_points_label->setVisible(true); // Set the label to be visible by default
    plot_points_label->raise(); // Set z-index to highest

    // Create a label for showing the plot points
    QLabel *pointLabel = new QLabel(realtime_chartView);
    pointLabel->setStyleSheet("QLabel { background-color: #22222; color: white; border: 1px solid white; border-radius: 2px; font-weight: bold; }"); // Modify the style sheet to make the labels bold
    pointLabel->setGeometry(QRect(0, 0, 120, 40)); // Make the label bigger
    pointLabel->setVisible(true); // Set the label to be visible by default
    pointLabel->raise(); // Set z-index to highest


    QObject::connect(realtime_chartView, &QChartView::rubberBandChanged, [=](const QRectF &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint) { // Connect the signal of the chart view to a custom slot
        QPointF point = realtime_chartView->chart()->mapToValue(realtime_chartView->mapToScene(toScenePoint.toPoint()));

        plot_points_label->setText(QString("X: %1\nY: %2").arg(point.x()).arg(point.y())); // Update the label with the new x and y values
    });


    QObject::connect(realtime_series, &QLineSeries::clicked, [=](const QPointF &point) { // Connect the clicked signal of the series to a custom slot

        pointLabel->setText(QString("Point: (%1, %2)").arg(point.x()).arg(point.y())); // Update the point label text and position
        pointLabel->move(realtime_chartView->width() - pointLabel->width() - 5, realtime_chartView->height() - pointLabel->height() - 5);
    });


    QObject::connect(realtime_series, &QLineSeries::pointAdded, [=](int index) { // Connect the series signal to update the label as x value changes

        qreal x = realtime_series->at(index).x(); // Get the latest x value

        plot_points_label->setText(QString("X: %1\nY: %2").arg(x).arg(realtime_series->at(index).y())); // Update the label text
    });


    QVBoxLayout *realtime_layout = new QVBoxLayout(ui->realtime_chart_frame); // Add the chart view, label, and point label to the layout
    realtime_layout->addWidget(realtime_chartView);
    realtime_layout->addWidget(plot_points_label);
    realtime_layout->addWidget(pointLabel);
}


void MainWindow::advanceSlideshow()
{
    int nextIndex = (ui->SlideshowWid->currentIndex() + 1) % ui->SlideshowWid->count(); // Get the index of the next page in the slideshow by adding 1 to the current index and wrapping around to 0 when reaching the end
    QWidget* nextPage = ui->SlideshowWid->widget(nextIndex); // Get the widget for the next page and create a QGraphicsOpacityEffect object with opacity set to 0

    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(nextPage); // Create QGraphicsOpacityEffect object and set the opacity to 0
    nextPage->setGraphicsEffect(effect);
    effect->setOpacity(0.0);



    QPropertyAnimation* animFadeOut = new QPropertyAnimation(ui->SlideshowWid->currentWidget()->graphicsEffect(), "opacity"); // Create a fade out animation for the current widget with a duration of 1 second, starting at full opacity and ending at 0 opacity
    animFadeOut->setDuration(1000);
    animFadeOut->setStartValue(1.0);
    animFadeOut->setEndValue(0.0);


    QPropertyAnimation* animFadeIn = new QPropertyAnimation(effect, "opacity"); // Create a fade in animation for the next widget with a duration of 1 second, starting at 0 opacity and ending at full opacity
    animFadeIn->setDuration(1000);
    animFadeIn->setStartValue(0.0);
    animFadeIn->setEndValue(1.0);

    connect(animFadeOut, &QPropertyAnimation::finished, this, [=]() { // Connect the finished() signal of the fade out animation to a lambda function that sets the current index to the next index and starts the fade in animation
        ui->SlideshowWid->setCurrentIndex(nextIndex);
        animFadeIn->start();
    });


    animFadeOut->start(); // Start the animations
}






//adding new tabs! ========================================
void MainWindow::on_addTabNameButton_clicked()
{

    QTabWidget* tabWidget = ui->tabChartWidget; //Making the widgets in ui
    QLineEdit* lineEdit = ui->nametab;


    QString tabName = lineEdit->text(); //Getting the text from the LineEdit

    std::string whole_preference = tabName.toStdString(); // Converting the string from QString to normal string.
    std::vector<std::string> preferences_split; // Using vectors to have the preferences split from the whole string.

    std::stringstream ss_pref(whole_preference); // Using stringstream to be able to use the getline to split the string.
    std::string preferences_split_part; // The parts that are going to be pushed back to the vector

    if(whole_preference.size()!=0)
        while (std::getline(ss_pref, preferences_split_part, ':')) {
            preferences_split.push_back(preferences_split_part); // Pushing the values in the vector
        }
    else
        return;



    int parses = std::stoi(preferences_split.at(1)); // Number of the preferred charts

    QGridLayout *layout = new QGridLayout; // Makes the layout be a grid





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


        int dialogX = (mainWidth - loadingDialog.width()) / 2; // Calculate the position of the loading dialog
        int dialogY = (mainHeight - loadingDialog.height()) / 2;


        loadingDialog.move(dialogX, dialogY); // Move the loading dialog to the center of the main window


        setDisabled(true);  // Disable the main window


        loadingDialog.show(); // Show the loading dialog
        QApplication::processEvents();

        layout->addWidget(frameArray[frameArray.size()-1], 0, 0); // Run the long-running code
        std::vector<double> DataRead = Firestore_Read_Data(preferences_split.at(parses+1).c_str()); // This line declares a vector of doubles named DataRead and initializes it with data retrieved from Firestore.


        QChart *chart = new QChart(); // This line creates a new chart object and sets its theme to a dark style. It also sets the chart's background to transparent and sets its title.
        chart->setTheme(QChart::ChartThemeDark);
        chart->setBackgroundBrush(QBrush(Qt::transparent));
        chart->setTitle(preferences_split.at(parses+1).c_str());
        QVector<QPointF> points; // This line declares a QVector of QPointF objects named points.
        int N = DataRead.size(); // This line initializes an integer variable N with the size of DataRead.
        int frontN, rearN; // These lines declare integer variables frontN and rearN and initialize the boolean flagN.
        bool flagN = false;


        for(int i=0; i<dateOfChartContent.size(); i++) // This loop prints out the elements of the dateOfChartContent vector.
            std::cout << dateOfChartContent[i] << std::endl;


        QString dateString = QString::fromStdString(dateOfChartContent[dateOfChartContent.size()-1]); // This line gets the last date string from the dateOfChartContent vector and extracts the date part.
        QStringList parts = dateString.split(" ");
        QString dateStrBreak = parts[0]; // Get the first part (the date)


        for(int i=0; i<dateOfChartContent.size(); i++){ // This for loop iterates through the elements of the date vector
            QString dateString = QString::fromStdString(dateOfChartContent[i]); // Converts a string from the date vector to a QString object
            QStringList parts = dateString.split(" "); // Splits the QString object into multiple parts separated by a space and stores them in a QStringList object called parts
            QString dateStr = parts[0]; // Retrieves the first part (the date) of the QStringList object and stores it in a QString object called dateStr
            if(preferences_split.at(parses+2).c_str()==dateStr.toStdString() && flagN==false){ // Checks if the date in preferences_split is equal to the date in dateStr and flagN is false
                frontN=i; // If the condition is true, then sets frontN to i and sets flagN to true
                flagN=true;
            }
            if(preferences_split.at(parses+2).c_str()!=dateStr.toStdString() && flagN==true){ // Checks if the date in preferences_split is not equal to the date in dateStr and flagN is true
                rearN= i-1; // If the condition is true, then sets rearN to i-1 and breaks the loop
                break;
            }
            if(dateStrBreak.toStdString()==dateStr.toStdString() && flagN==true){ // Checks if the date in dateStr is equal to dateStrBreak and flagN is true
                rearN=dateOfChartContent.size()-1; // If the condition is true, then sets rearN to the last index of dateOfChartContent and breaks the loop
                break;
            }
        }

        dateOfChartContent.clear(); // Clears the elements in dateOfChartContent

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


        QObject::connect(series, &QLineSeries::hovered, [=](const QPointF &point, bool state) {  // Connect the hovered signal of the series to a custom slot
            if (state) {

                label->setVisible(true); // Show the label and update its text
                label->setText(QString("X: %1\nY: %2").arg(point.x()).arg(point.y()));


                QPoint mousePos = chartView->mapFromGlobal(QCursor::pos()); // Move the label to the current mouse position
                label->move(mousePos.x() - label->width()/2, mousePos.y() - label->height() - 5); // Space out the label
            } else {

                label->setVisible(false); // Hide the label
            }
        });





        // Hide the loading dialog and enable the main window
        loadingDialog.hide();
        setDisabled(false);






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

void MainWindow::create_chart(/*final_name, */std::vector<QFrame*> frameArray, int parses){
    qDebug() << "HEREEEEE VECTOR--->" << vector_counter_chart;
}
