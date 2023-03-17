#include "login_sign_up_in.h"
#include "mainwindow.h"
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
//#include "databasehandler1.h"
//end of file and headers (#include)
//hello_test


namespace myNamespace{
    float fin_ans,sec_ans;
    float ok;
    std::vector<QString> passwords;
    std::vector<QString> emails;
}

namespace username_change{
    extern std::vector<std::string> full_name;
}

int main(int argc, char *argv[])
{


    QApplication app(argc, argv); //creates the application



    login_sign_up_in loginWindow;
    loginWindow.setWindowModality(Qt::ApplicationModal);
    QNetworkAccessManager manager;
        QNetworkRequest request(QUrl("https://realtimeqttest-default-rtdb.europe-west1.firebasedatabase.app/Emails.json"));

        QNetworkReply *reply = manager.get(request);

        QObject::connect(reply, &QNetworkReply::finished, [&]() {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
                QJsonObject jsonObject = jsonDoc.object();


                for (auto iter = jsonObject.constBegin(); iter != jsonObject.constEnd(); ++iter) {
                    QString key = iter.key();
                    QString value = iter.value().toString();

                    if (value.contains("@")) {
                        myNamespace::emails.push_back(value);
                    }
                }

                // print the emails in the vector
                for (const auto& email : myNamespace::emails) {
                    std::cout << email.toStdString() << std::endl;
                }
            reply->deleteLater();
        });


        QNetworkAccessManager manager1;
            QNetworkRequest request1(QUrl("https://realtimeqttest-default-rtdb.europe-west1.firebasedatabase.app/Passwords.json"));

            QNetworkReply *reply1 = manager1.get(request1);

            QObject::connect(reply1, &QNetworkReply::finished, [&]() {
                QByteArray data1 = reply1->readAll();
//                QString qans = QString::fromUtf8(data1);
//                       std::string c_ans = qans.toStdString();
//                       qDebug() << "JSON data:" << qans;
                QJsonDocument jsonDoc1 = QJsonDocument::fromJson(data1);
                    QJsonObject jsonObject1 = jsonDoc1.object();





            QNetworkAccessManager manager2;
                QNetworkRequest request2(QUrl("https://realtimeqttest-default-rtdb.europe-west1.firebasedatabase.app/FullName.json"));

                QNetworkReply *reply2 = manager2.get(request2);

                QObject::connect(reply2, &QNetworkReply::finished, [&]() {
                    QByteArray data2 = reply2->readAll();
    //                QString qans = QString::fromUtf8(data1);
    //                       std::string c_ans = qans.toStdString();
    //                       qDebug() << "JSON data:" << qans;
                    QJsonDocument jsonDoc2 = QJsonDocument::fromJson(data2);
                        QJsonObject jsonObject2 = jsonDoc2.object();

                        for (auto iter2 = jsonObject2.constBegin(); iter2 != jsonObject2.constEnd(); ++iter2) {
                            QString key2 = iter2.key();
                            QString value2 = iter2.value().toString();
                            std::string value_last = value2.toStdString();
                            username_change::full_name.push_back(value_last);
                        }

                    reply2->deleteLater();
                });


                        for (auto iter2 = jsonObject2.constBegin(); iter2 != jsonObject2.constEnd(); ++iter2) {
                            QString key2 = iter2.key();
                            QString value2 = iter2.value().toString();
                            std::string value_last = value2.toStdString();
                            username_change::full_name.push_back(value_last);
                        }

                    reply2->deleteLater();
                });


    //start of real time reading from firebase
    QNetworkAccessManager realtime_manager;

    // creating a QThread to run the timer on
    QThread thread;
    // setting up the request
    QNetworkRequest realtime_request;
    request.setUrl(QUrl("https://realtimeqttest-default-rtdb.europe-west1.firebasedatabase.app/Dog.json"));

    // creating a QTimer to send requests at regular intervals
    QTimer timer;
    timer.start(100); // send a request every 100 milli-seconds

    // put timer and manager to same thread
    realtime_manager.moveToThread(&thread);
    timer.moveToThread(&thread);



    // connect the timeout signal of the timer to a slot that sends the request and processes the response
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        // sending the request and waiting for the response
        QNetworkReply *reply = realtime_manager.get(request);
        // creating an event loop to process the response
        QEventLoop realtime_loop;
        QAbstractSocket::connect(reply, &QNetworkReply::finished, &realtime_loop, &QEventLoop::quit); //if there is data it then stops the connection
        realtime_loop.exec();

        // printf the response data
        QString qans = reply->readAll(); //convert to QString
        std::string c_ans = qans.toStdString(); //convert to regural C++ string

        //removing '"' and holding on to '.' for it to be converted to float
        c_ans.erase(std::remove_if(c_ans.begin(), c_ans.end(), [](char c){return !std::isdigit(c) && c != '.' && c != ' ';}), c_ans.end());

        std::string first,second; //defining the first and the second numbers

        std::stringstream ss(c_ans);
        ss >> first >> second; //spliting the string on space




        myNamespace::fin_ans = atof(first.c_str()); //convert to float
        myNamespace::sec_ans = atof(second.c_str()); //also
        std::cout << std::setprecision(12) << myNamespace::fin_ans << "  |||  " << std::setprecision(8) << myNamespace::sec_ans << std::endl; //print output
//        with float precision (counting the decimal numbers also) 12.

    });

    //start the thread
    thread.start();
    ////end of reading from firebase
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
