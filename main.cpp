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


//end of file and headers (#include)

const QString kProjectId = "realtimeqttest";

const QString kDocumentId = "FrontBrakes";

void ReadFromFirestore(QNetworkAccessManager* qnam) {
  // Set up the URL for the Firestore REST API
  QUrl url(QString("https://firestore.googleapis.com/v1/projects/%1/databases/(default)/documents/ChartFiles/%2").arg(kProjectId).arg(kDocumentId));

  // Set up the request
  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  // Make the GET request
  QNetworkReply* reply = qnam->get(request);

  // Wait for the response
  while (!reply->isFinished()) { }

  // Check the response status code
  if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
    // Parse the JSON response
    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonObject = jsonDoc.object();

    // Print the data from the document
    qDebug() << "Document data: " << jsonObject["fields"].toObject();
  } else {
    std::cout << "Error reading document" << std::endl;
  }

  // Clean up
  reply->deleteLater();
}

int main(int argc, char *argv[])
{

    QApplication app(argc, argv); //creates the application
//    getRealTimeData();


//    // Create a QNetworkAccessManager
//     QNetworkAccessManager* qnam = new QNetworkAccessManager();

//     // Read data from Firestore
//     ReadFromFirestore(qnam);

    // creating a qnetworkmanager
    QNetworkAccessManager manager;

    // creating a QThread to run the timer on
    QThread thread;
    // setting up the request
    QNetworkRequest request;
    request.setUrl(QUrl("https://realtimeqttest-default-rtdb.europe-west1.firebasedatabase.app/Dog.json"));

    // creating a QTimer to send requests at regular intervals
    QTimer timer;
    timer.start(100); // send a request every 100 milli-seconds

    // put timer and manager to same thread
    manager.moveToThread(&thread);
    timer.moveToThread(&thread);


    // connect the timeout signal of the timer to a slot that sends the request and processes the response
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        // sending the request and waiting for the response
        QNetworkReply *reply = manager.get(request);

        // creating an event loop to process the response
        QEventLoop loop;
        QAbstractSocket::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit); //if there is data it then stops the connection
        loop.exec();

        // printf the response data
        QString qans = reply->readAll(); //convert to QString
        std::string c_ans = qans.toStdString(); //convert to regural C++ string

        //removing '"' and holding on to '.' for it to be converted to float
        c_ans.erase(std::remove_if(c_ans.begin(), c_ans.end(), [](char c){return !std::isdigit(c) && c != '.' && c != ' ';}), c_ans.end());

        std::string first,second; //defining the first and the second numbers

        std::stringstream ss(c_ans);
        ss >> first >> second; //spliting the string on space





//        long double fin_ans = std::stold(first); //convert to float
//        long double sec_ans = std::stold(second); //also
//        std::cout << std::setprecision(12) << fin_ans << "  |||  " << std::setprecision(8) << sec_ans << std::endl; //print output
        //with float precision (counting the decimal numbers also) 12.

    });

    // Start the thread
    thread.start();
    MainWindow w;
    w.show();
//    databasehandler1 dbhandler;
    return app.exec();
}
