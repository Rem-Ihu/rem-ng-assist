#include "databasehandler1.h"


void getRealTimeData(){
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


        long double fin_ans = std::stold(first); //convert to float
        long double sec_ans = std::stold(second); //also
        std::cout << std::setprecision(12) << fin_ans << "  |||  " << std::setprecision(8) << sec_ans << std::endl; //print output
        //with float precision (counting the decimal numbers also) 12.

    });

    // Start the thread
    thread.start();
    timer.stop();
//    manager.stop();
}
