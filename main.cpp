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
//end of file and headers (#include)




namespace myNamespace{
    float first_realtime_answer,second_realtime_answer;
    float ok;
    std::vector<QString> passwords;
    std::vector<QString> emails;
}

namespace username_change{
    extern std::vector<std::string> full_name;
}

int main(int argc, char *argv[])
{

    QApplication app(argc, argv); // Creates the application



    login_sign_up_in loginWindow;
    loginWindow.setWindowModality(Qt::ApplicationModal);
    QNetworkAccessManager email_manager; // Create a new instance of QNetworkAccessManager for the emails
        QNetworkRequest email_request(QUrl("https://realtimeqttest-default-rtdb.europe-west1.firebasedatabase.app/Emails.json")); // Create a QNetworkRequest object with the URL of the JSON file to be downloaded

        QNetworkReply *email_reply = email_manager.get(email_request); // Send a GET request to the server and get a QNetworkReply object

        QObject::connect(email_reply, &QNetworkReply::finished, [&]() { // Connect a lambda function to the finished signal of the QNetworkReply object
            QByteArray emails_data = email_reply->readAll(); // Read the response data from the QNetworkReply object
            QJsonDocument email_jsonDoc = QJsonDocument::fromJson(emails_data); // Parse the response data as a JSON document
                QJsonObject email_jsonObject = email_jsonDoc.object(); // Extract the JSON object from the JSON document


                for (auto email_iterator = email_jsonObject.constBegin(); email_iterator != email_jsonObject.constEnd(); ++email_iterator) { // Iterate over each key-value pair in the JSON object
                    QString email_key = email_iterator.key(); // Extract the key and value of the current key-value pair
                    QString email_value = email_iterator.value().toString();

                    if (email_value.contains("@")) { // Check if the value is a valid email address
                        myNamespace::emails.push_back(email_value); // Add the email address to the global vector variable in the "myNamespace" namespace
                    }
                }

                // Print the emails in the vector
                for (const auto& email : myNamespace::emails) {
                    std::cout << email.toStdString() << std::endl;
                }
            email_reply->deleteLater(); // Free the memory allocated for the QNetworkReply object
        });


        QNetworkAccessManager password_manager; // Create a QNetworkAccessManager object to make network requests for the passwords
            QNetworkRequest password_request(QUrl("https://realtimeqttest-default-rtdb.europe-west1.firebasedatabase.app/Passwords.json")); // Create a QNetworkRequest object to specify the URL for the network request

            QNetworkReply *password_reply = password_manager.get(password_request); // Make a GET request to retrieve data from the specified URL and store the QNetworkReply object

            QObject::connect(password_reply, &QNetworkReply::finished, [&]() { // Use a lambda function to connect to the "finished" signal of the QNetworkReply object
                QByteArray password_data = password_reply->readAll(); // Read the data from the network reply into a QByteArray object
                QJsonDocument password_jsonDoc = QJsonDocument::fromJson(password_data); // Parse the data as a JSON document
                    QJsonObject password_jsonObject = password_jsonDoc.object(); // Get the JSON object from the parsed JSON document



                    for (auto password_iterator = password_jsonObject.constBegin(); password_iterator != password_jsonObject.constEnd(); ++password_iterator) { // Iterate over the key-value pairs in the JSON object
                        QString password_key = password_iterator.key(); // Get the key as a QString
                        QString password_value = password_iterator.value().toString(); // Get the value as a QString
                        myNamespace::passwords.push_back(password_value); // Add the password to the password vector in the myNamespace namespace
                    }
                    for (const auto& passwords : myNamespace::passwords) { // Print the passwords in the vector
                        std::cout << passwords.toStdString() << std::endl;
                    }
                password_reply->deleteLater();// Free the memory allocated for the QNetworkReply object
            });


            QNetworkAccessManager fullname_manager; // Create an instance of QNetworkAccessManager to handle network requests
                QNetworkRequest fullname_request(QUrl("https://realtimeqttest-default-rtdb.europe-west1.firebasedatabase.app/FullName.json")); // Create a network request for retrieving the full name data from a Firebase Realtime Database

                QNetworkReply *fullname_reply = fullname_manager.get(fullname_request); // Send the network request and receive a QNetworkReply pointer in response

                QObject::connect(fullname_reply, &QNetworkReply::finished, [&]() { // Connect a function to the QNetworkReply::finished signal to be executed when the reply is finished
                    QByteArray fullname_data = fullname_reply->readAll(); // Read the response data from the QNetworkReply
                    QJsonDocument fullname_jsonDoc = QJsonDocument::fromJson(fullname_data); // Convert the response data from QByteArray to QJsonDocument
                        QJsonObject fullname_jsonObject = fullname_jsonDoc.object(); // Extract the JSON object from the QJsonDocument



                        for (auto fullname_iterator = fullname_jsonObject.constBegin(); fullname_iterator != fullname_jsonObject.constEnd(); ++fullname_iterator) { // Iterate over the JSON object and extract the key-value pairs
                            QString fullname_key = fullname_iterator.key();
                            QString fullname_value = fullname_iterator.value().toString();
                            std::string fullname_value_string = fullname_value.toStdString(); // Convert the QString value to std::string
                            username_change::full_name.push_back(fullname_value_string); // Add the std::string value to a vector
                        }

                    fullname_reply->deleteLater();
                });


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


