#ifndef FIREBASEGET_H
#define FIREBASEGET_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <iostream>

using namespace std;

class firebaseGet
{
public:
    firebaseGet();
private:
    void getEmails();
    void getPasswords();
    void getFullNames();
};

#endif // FIREBASEGET_H
