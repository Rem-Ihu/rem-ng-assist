#ifndef DATABASEHANDLER1_H
#define DATABASEHANDLER1_H


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



 //global vector value for charts.
bool frame_go_ahead = false;
namespace myNamespace2{
    int number_of_frames = 0;
//    double* array = (double*) malloc(N*sizeof(double));
}



std::vector<double> Firestore_Read_Data(std::string chart_id){
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QUrl url("https://firestore.googleapis.com/v1/projects/realtimeqttest/databases/(default)/documents/ChartFiles/" + QString::fromStdString(chart_id));
    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);
    std::vector<double> vec_val;
    QEventLoop loop; // create a new event loop
    QObject::connect(reply, &QNetworkReply::finished, [&loop, reply, &vec_val]() {
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
            loop.quit(); // quit the event loop if there's an error
            return;
        }
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonObject fields = jsonObject["fields"].toObject();
        QJsonArray data = fields["data"].toObject()["arrayValue"].toObject()["values"].toArray();
//        std::vector<double> vec_val;
        QDateTime timestamp;

        for (int i = 0; i < data.size(); i++) {
            QJsonObject mapValue = data[i].toObject()["mapValue"].toObject()["fields"].toObject();
            QString timestampStr = mapValue["timestamp"].toObject()["timestampValue"].toString();
            timestamp = QDateTime::fromString(timestampStr, Qt::ISODateWithMs);

            bool ok = false;
            int intValue = mapValue["value"].toObject()["integerValue"].toString().toInt(&ok);
            if (ok) {
                double doubleValue = static_cast<double>(intValue);
                vec_val.push_back(doubleValue);
            } else {
                double doubleValue = mapValue["value"].toObject()["doubleValue"].toDouble();
                vec_val.push_back(doubleValue);
            }
        }

        loop.quit(); // quit the event loop when the reply is finished
    });

    loop.exec(); // start the event loop and wait until it quits

    return vec_val;
}



#endif // DATABASEHANDLER1_H
