//#include "databasehandler1.h"
#include "mainwindow.h"
//#include "firebase/app.h"
# include <QApplication>
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
//PDF_Drawings/03-SWINGRIGHT-004-002_DRAWING.svg


//end of file and headers (#include)

void Firestore_Read_Data(){



    QNetworkAccessManager* manager = new QNetworkAccessManager();

        // Set up the QNetworkRequest with the URL of the Firestore endpoint you want to access
        QUrl url("https://firestore.googleapis.com/v1/projects/realtimeqttest/databases/(default)/documents/ChartFiles/FrontBrakes");
        QNetworkRequest request(url);

        // Set the authentication headers if needed
//        request.setRawHeader("Authorization", "Bearer YOUR_AUTH_TOKEN");

        // Send the GET request and retrieve the reply
        QNetworkReply* reply = manager->get(request);

        // Connect the signal QNetworkReply::finished() to the slot handleResponse
        QObject::connect(reply, &QNetworkReply::finished, [reply]() {
            if (reply->error()) {
                qDebug() << "Error:" << reply->errorString();
                return;
            }
            QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
            QJsonObject jsonObject = jsonResponse.object();
            QJsonObject fields = jsonObject["fields"].toObject();
            int seconds = fields["Seconds"].toObject()["integerValue"].toString().toInt();
            int value = fields["Value"].toObject()["integerValue"].toString().toInt();
            std::cout << "Seconds: " << seconds <<std::endl;
            std::cout << "Value: " << value<<std::endl;
        });

}


int main(int argc, char *argv[])
{


    QApplication app(argc, argv); //creates the application


//    Firestore_Read_Data();


    QFile file("main.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);


    QNetworkAccessManager *manager = new QNetworkAccessManager();

    // Create the JSON object with the field values
    QJsonObject json;
    json.insert("Seconds", 10);
    json.insert("Value", 20);

    // Convert the JSON object to a string
    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    // Create the request to add the document
    QUrl url("https://firestore.googleapis.com/v1/projects/realtimeqttest/databases/(default)/documents/ChartFiles/Testing");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//    request.setRawHeader("Authorization", "Bearer " + ACCESS_TOKEN);

    // Send the request to add the document
    QNetworkReply *reply = manager->post(request, jsonData);

    // Connect to the finished signal to handle the response
    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            // Handle error
            qDebug() << "Error: " << reply->errorString();
        } else {
            // Handle success
            qDebug() << "Successfully added document.";
        }
        reply->deleteLater();
    });

//        QNetworkAccessManager manager;

//        // creating a QThread to run the timer on
//        QThread thread;
//        // setting up the request
//        QNetworkRequest request;
//        request.setUrl(QUrl("https://realtimeqttest-default-rtdb.europe-west1.firebasedatabase.app/Dog.json"));

//        // creating a QTimer to send requests at regular intervals
//        QTimer timer;
//        timer.start(100); // send a request every 100 milli-seconds

//        // put timer and manager to same thread
//        manager.moveToThread(&thread);
//        timer.moveToThread(&thread);



//        // connect the timeout signal of the timer to a slot that sends the request and processes the response
//        QObject::connect(&timer, &QTimer::timeout, [&]() {
//            // sending the request and waiting for the response
//            QNetworkReply *reply = manager.get(request);

//            // creating an event loop to process the response
//            QEventLoop loop;
//            QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit); //if there is data it then stops the connection
//            loop.exec();

//            // printf the response data
//            QString qans = reply->readAll(); //convert to QString
//            std::string c_ans = qans.toStdString(); //convert to regural C++ string

//            //removing '"' and holding on to '.' for it to be converted to float
//            c_ans.erase(std::remove_if(c_ans.begin(), c_ans.end(), [](char c){return !std::isdigit(c) && c != '.' && c != ' ';}), c_ans.end());

//            std::string first,second; //defining the first and the second numbers

//            std::stringstream ss(c_ans);
//            ss >> first >> second; //spliting the string on space




//            long double fin_ans = atof(first.c_str()); //convert to float
//            long double sec_ans = atof(second.c_str()); //also
//            std::cout << std::setprecision(12) << fin_ans << "  |||  " << std::setprecision(8) << sec_ans << std::endl; //print output
//    //        with float precision (counting the decimal numbers also) 12.

//    });

    // Start the thread        
    //thread.start();

    MainWindow w;
    w.show();
//    databasehandler1 dbhandler;
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
