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



 //Global vector value for charts.
bool frame_go_ahead = false;
namespace myNamespace2{
    int number_of_frames = 0;
}
std::vector<std::string> dateOfChartContent;

//Definition of the function responsible for fetching data from the database
std::vector<double> Firestore_Read_Data(std::string chart_id){
    QNetworkAccessManager* manager = new QNetworkAccessManager();// Create a new instance of QNetworkAccessManager to handle network requests
    QUrl url("https://firestore.googleapis.com/v1/projects/realtimeqttest/databases/(default)/documents/ChartFiles/" + QString::fromStdString(chart_id));// The URL for the Firestore database with the chart_id appended to it
    QNetworkRequest request(url);// Create a new network request with the given URL
    QNetworkReply* reply = manager->get(request);// Send a GET request using the manager and store the reply
    std::vector<double> vec_val; // Create an empty vector to store the data read from the database
    QEventLoop loop; // Create a new event loop
    QObject::connect(reply, &QNetworkReply::finished, [&loop, reply, &vec_val]() {// Connect a lambda function to the finished signal of the network reply
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
            loop.quit(); // Quit the event loop if there's an error
            return;
        }
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());// Convert the network reply to a JSON document and extract the object from it
        QJsonObject jsonObject = jsonResponse.object();
        QJsonObject fields = jsonObject["fields"].toObject();// Extract the "fields" object from the JSON object
        QJsonArray data = fields["data"].toObject()["arrayValue"].toObject()["values"].toArray();// Extract the "data" array from the "fields" object
        QDateTime timestamp;// Create a QDateTime object to store the timestamp for each data point

        for (int i = 0; i < data.size(); i++) {// Loop through each element in the "data" array
            QJsonObject mapValue = data[i].toObject()["mapValue"].toObject()["fields"].toObject();// Extract the "fields" object from the "mapValue" object in the array
            QString timestampStr = mapValue["timestamp"].toObject()["timestampValue"].toString();// Extract the timestamp string from the "timestampValue" object and convert it to a QDateTime object
            timestamp = QDateTime::fromString(timestampStr, Qt::ISODateWithMs);
            std::string date = timestamp.toString("yyyy/MM/dd hh:mm:ss ap").toStdString();// Convert the QDateTime object to a string and store it in a vector
            dateOfChartContent.push_back(date);
            bool ok = false;// Extract the value from the "value" object in the "mapValue" object
            int intValue = mapValue["value"].toObject()["integerValue"].toString().toInt(&ok);
            if (ok) {// If the value is an integer, cast it to a double and add it to the vector
                double doubleValue = static_cast<double>(intValue);
                vec_val.push_back(doubleValue);
            } else {// If the value is not an integer, extract it as a double and add it to the vector
                double doubleValue = mapValue["value"].toObject()["doubleValue"].toDouble();
                vec_val.push_back(doubleValue);
            }
        }

        loop.quit(); // Quit the event loop when the reply is finished
    });

    loop.exec(); // Start the event loop and wait until it quits

    return vec_val; //Return the vector with the appropriate values
}



#endif // DATABASEHANDLER1_H
