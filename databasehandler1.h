#ifndef DATABASEHANDLER1_H
#define DATABASEHANDLER1_H


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
#include <QCoreApplication>
#include <QSvgRenderer>
#include <QStackedWidget>
#include <iostream>


std::vector<int> vec_val; //global vector value for charts

void Firestore_Read_Data(std::string chart_id){

    QNetworkAccessManager* manager = new QNetworkAccessManager();

    //creating the url
    QUrl url("https://firestore.googleapis.com/v1/projects/realtimeqttest/databases/(default)/documents/ChartFiles/" + QString::fromStdString(chart_id));//adding the chart id for getting the correct url and convrting it first to QString

    QNetworkRequest request(url); //setting the url request

    // Send the GET request and retrieve the reply
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



        //parsing through the data
        for (int i = 0; i < data.size(); i++) {
            /*  1.  QJsonObject mapValue = data[i].toObject()["mapValue"].toObject()["fields"].toObject();
                This line extracts the i-th element of the "values" array from the "data" object,
                and then extracts the "mapValue" object and the "fields" object from it.
                Finally, it converts the "fields" object to a QJsonObject called "mapValue".
                In the Firestore document, the "mapValue" object represents a map or dictionary data type,
                and the "fields" object within it represents key-value pairs.

                2.  QString timestampStr = mapValue["timestamp"].toObject()["timestampValue"].toString();
                This line extracts the value of the "timestampValue" key from the "timestamp" object within
                the "mapValue" object. It then converts the value to a QString variable called "timestampStr".
                In the Firestore document, the "timestampValue" key represents a timestamp data type.

                3.  timestamp = QDateTime::fromString(timestampStr, Qt::ISODateWithMs); This line converts
                the QString variable "timestampStr" to a QDateTime object, using the fromString() function of the QDateTime
                class. The second argument to the function is a string that specifies the format of the input string.
                In this case, the format is ISO 8601 with milliseconds precision. The resulting QDateTime object is
                stored in the "timestamp" variable.

                4.  int value = mapValue["value"].toObject()["integerValue"].toString().toInt(); This line
                extracts the value of the "integerValue" key from the "value" object within the "mapValue" object.
                It then converts the value to an integer and stores it in the "value" variable. In the
                Firestore document, the "integerValue" key represents an integer data type.*/

            //1.
            QJsonObject mapValue = data[i].toObject()["mapValue"].toObject()["fields"].toObject();
            //2.
            QString timestampStr = mapValue["timestamp"].toObject()["timestampValue"].toString();
            //3.
            timestamp = QDateTime::fromString(timestampStr, Qt::ISODateWithMs);
            //4.
            int value = mapValue["value"].toObject()["integerValue"].toString().toInt();

            vec_val.push_back(value);//vector for the resulting values
            vec_val.shrink_to_fit();

            //printing the modified results
            qDebug() << "Timestamp:" << timestamp.toString("yyyy-MM-dd hh:mm:ss.zzz") << "Value:" << value;
        }

    });

//    for (auto i = vec_val.begin(); i != vec_val.end(); ++i)
//            std::cout << *i << " ";

}
#endif // DATABASEHANDLER1_H
