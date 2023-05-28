#include "login_sign_up_in.h"
#include "mainwindow.h"
#include "firebaseget.h"
#include "realtimedatastream.h"
#include <iostream>
#include <fstream>
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QtQuick3D/qquick3d.h>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>
#include <QVariant>
#include <QString>
#include <QSocketDescriptor>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <iostream>
#include <QMutex>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QtCore>
#include <QtWidgets>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCoreApplication>
#include <QSvgRenderer>
#include <QStackedWidget>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <QFile>
#include <QTextStream>
//end of file and headers (#include)




namespace myNamespace{
    float first_realtime_answer,second_realtime_answer;
    float ok;
    std::vector<QString> passwords;
    extern std::vector<QString> emails;
}

namespace username_change{
    extern std::vector<std::string> full_name;
}

int main(int argc, char *argv[])
{

    QApplication app(argc, argv); // Creates the application

//    realtimeDataStream();

    firebaseGet();


    //REALTIME EVENT MANAGER
    QNetworkAccessManager realtime_manager;  // Start of real time reading from firebase
    QThread realtime_thread; // Creating a QThread to run the timer on
    QNetworkRequest realtime_request; // Setting up the request
    realtime_request.setUrl(QUrl("https://realtimeqttest-default-rtdb.europe-west1.firebasedatabase.app/Dog.json"));
    QTimer realtime_timer; // Creating a QTimer to send requests at regular intervals
    realtime_timer.start(100); // Send a request every 100 milli-seconds
    realtime_manager.moveToThread(&realtime_thread); // Put timer and manager to same thread
    realtime_timer.moveToThread(&realtime_thread);




    QObject::connect(&realtime_timer, &QTimer::timeout, [&]() { // Connect the timeout signal of the timer to a slot that sends the request and processes the response

        QNetworkReply *realtime_reply = realtime_manager.get(realtime_request); // Sending the request and waiting for the response

        QEventLoop realtime_loop; // Creating an event loop to process the response
        QAbstractSocket::connect(realtime_reply, &QNetworkReply::finished, &realtime_loop, &QEventLoop::quit); // If there is data it then stops the connection
        realtime_loop.exec();
        QString realtime_Qstring = realtime_reply->readAll(); // Convert to QString
        std::string realtime_C_string = realtime_Qstring.toStdString(); // Convert to regural C++ string


        realtime_C_string.erase(std::remove_if(realtime_C_string.begin(), realtime_C_string.end(), [](char c){return !std::isdigit(c) && c != '.' && c != ' ';}), realtime_C_string.end()); // Removing '"' and holding on to '.' for it to be converted to float

        std::string first_number,second_number; // Defining the first and the second numbers

        std::stringstream realtime_stringstream(realtime_C_string);
        realtime_stringstream >> first_number >> second_number; // Spliting the string on space




        myNamespace::first_realtime_answer = atof(first_number.c_str()); // Convert to float
        myNamespace::second_realtime_answer = atof(second_number.c_str()); // Also
        std::cout << std::setprecision(12) << myNamespace::first_realtime_answer << "  |||  " << std::setprecision(8) << myNamespace::second_realtime_answer << std::endl; //print output with float precision (counting the decimal numbers also) 12
    });



    realtime_thread.start(); // Start the thread


    login_sign_up_in loginWindow;
    loginWindow.setWindowModality(Qt::ApplicationModal);



    loginWindow.show();

    return app.exec();
}
















/*


    QNetworkAccessManager manager;

        // creating a QThread to run the timer on
        QThread thread;
        // setting up the request for the first key
        QNetworkRequest request1;
        request1.setUrl(QUrl("https://realtimeqttest-default-rtdb.europe-west1.firebasedatabase.app/Dog.json"));

        // setting up the request for the second key
        QNetworkRequest request2;
        request2.setUrl(QUrl("https://realtimeqttest-default-rtdb.europe-west1.firebasedatabase.app/Cat.json"));

        // creating a QTimer to send requests at regular intervals
        QTimer timer;
        timer.start(50); // send a request every 50 milli-seconds

        // put timer and manager to same thread
        manager.moveToThread(&thread);
        timer.moveToThread(&thread);

        // connect the timeout signal of the timer to a slot that sends the requests and processes the responses
        QObject::connect(&timer, &QTimer::timeout, [&]() {
            // sending the request for the first key and waiting for the response
            QNetworkReply *reply1 = manager.get(request1);

            // creating an event loop to process the response
            QEventLoop loop1;
            QAbstractSocket::connect(reply1, &QNetworkReply::finished, &loop1, &QEventLoop::quit);
            loop1.exec();

            QNetworkReply *reply2 = manager.get(request2);

            // creating an event loop to process the response
            QEventLoop loop2;
            QAbstractSocket::connect(reply2, &QNetworkReply::finished, &loop2, &QEventLoop::quit);
            loop2.exec();
            // printf the response data
            QString qans = reply1->readAll();
            double number1 = qans.toDouble();
            int number2 = reply2->readAll().toInt();
            std::cout << std::setprecision(12) << number1 << "   " << number2 << std::endl;



*/


