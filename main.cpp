#include "databasehandler1.h"
#include "mainwindow.h"
#include <QTimer>
//end of file and headers (#include) asdasd






int main(int argc, char *argv[])
{


    QApplication app(argc, argv); //creates the application


    //test string for firestore url
    std::string chart_id = "ID1";
    Firestore_Read_Data(chart_id);








//start of real time reading from firebase
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




            long double fin_ans = atof(first.c_str()); //convert to float
            long double sec_ans = atof(second.c_str()); //also
            std::cout << std::setprecision(12) << fin_ans << "  |||  " << std::setprecision(8) << sec_ans << std::endl; //print output
    //        with float precision (counting the decimal numbers also) 12.

    });

    //start the thread
    thread.start();
//end of reading from firebase



    // In your main window class constructor:






    MainWindow w;
    w.show();
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
