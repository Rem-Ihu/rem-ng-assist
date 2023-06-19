#include "firebaseget.h"

namespace myNamespace{
    extern float first_realtime_answer,second_realtime_answer,ok;
    extern std::vector<QString> emails;
    extern std::vector<QString> passwords;
}

namespace username_change{
    extern int pass_check_number;
    extern std::vector<std::string> full_name;
}

firebaseGet::firebaseGet()
{
    getEmails();
    getPasswords();
    getFullNames();
}

void firebaseGet::getEmails(){

    QEventLoop loop; // Create a new event loop
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
            loop.quit();
        });
       loop.exec();
}


void firebaseGet::getPasswords(){

    QEventLoop loop; // Create a new event loop
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
            loop.quit();
        });
        loop.exec();
}


void firebaseGet::getFullNames(){

    QEventLoop loop; // Create a new event loop
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
            loop.quit();
        });
        loop.exec();
}
