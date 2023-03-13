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


std::vector<double> vec_val; //global vector value for charts.
namespace myNamespace2{
    int N = vec_val.size();
    double* array = (double*) malloc(N*sizeof(double));
}

void Firestore_Read_Data(std::string chart_id){

    QNetworkAccessManager* manager = new QNetworkAccessManager();

    //creating the url
    QUrl url("https://firestore.googleapis.com/v1/projects/realtimeqttest/databases/(default)/documents/ChartFiles/" + QString::fromStdString(chart_id));//adding the chart id for getting the correct url and convrting it first to QString

    QNetworkRequest request(url); //setting the url request

    //sending the GET request and retrieve the reply
    QNetworkReply* reply = manager->get(request);

    //creating the lambda function to connect and get the response from the reply
    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        //printing the error if it has one
        if (reply->error()) {
            qDebug() << "Error:" << reply->errorString();
            return;
        }

        //creating the json object from all the data that was received
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());

        //extracting the object from all the data
        QJsonObject jsonObject = jsonResponse.object();
        //extracting the fields from the object and making the fields json objects
        QJsonObject fields = jsonObject["fields"].toObject();
        //making the extracted data into an array (extracting the data from the arrayValue)
        QJsonArray data = fields["data"].toObject()["arrayValue"].toObject()["values"].toArray();

        QDateTime timestamp;



        for (int i = 0; i < data.size(); i++) {
            QJsonObject mapValue = data[i].toObject()["mapValue"].toObject()["fields"].toObject();
            QString timestampStr = mapValue["timestamp"].toObject()["timestampValue"].toString();
            timestamp = QDateTime::fromString(timestampStr, Qt::ISODateWithMs);

            //trying to extract the value as an int first
            bool ok = false;
            int intValue = mapValue["value"].toObject()["integerValue"].toString().toInt(&ok);
            if (ok) {
                double doubleValue = static_cast<double>(intValue);
                vec_val.push_back(doubleValue);
            } else {
                //if it's not an int, try to extract it as a double
                double doubleValue = mapValue["value"].toObject()["doubleValue"].toDouble();
                vec_val.push_back(doubleValue);
            }

            std::string testprintdate = timestamp.toString("yyyy-MM-dd hh:mm:ss.zzz").toStdString();

//            //printing the modified results
//            std::visit([](auto&& value){
//                if constexpr(std::is_same_v<double, decltype(value)>){
//                    std::cout << "THIS HERE " << value << std::endl;
//                } else if constexpr(std::is_same_v<int, decltype(value)>){
//                    std::cout << value << std::endl;
//                }
//            }, vec_val.back());
            myNamespace2::N = vec_val.size();
        }



        //printing the vector
        for (int i = 0; i < vec_val.size(); i++) {
            std::cout << vec_val[i] << std::endl;
        }

        for (int i = 0; i < myNamespace2::N; i++) {
            qDebug() << "1111111111--->" << vec_val[i];
            myNamespace2::array[i]=vec_val[i];
            qDebug() << "2222222222--->" << myNamespace2::array[i];
        }



    });

}
#endif // DATABASEHANDLER1_H
