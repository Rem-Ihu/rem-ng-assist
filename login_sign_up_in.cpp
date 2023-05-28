#include "login_sign_up_in.h"
#include "ui_login_sign_up_in.h"
#include <QMainWindow>
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
#include <QMap>
#include <QMutex>
#include <QTextStream>

namespace myNamespace{
    extern float first_realtime_answer,second_realtime_answer,ok;
    std::vector<QString> emails;
    extern std::vector<QString> passwords;
}

namespace username_change{
    int pass_check_number;
    std::vector<std::string> full_name;
}

login_sign_up_in::login_sign_up_in(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login_sign_up_in),
    mainwindow(nullptr)
{
    ui->setupUi(this);
    // Remove title bar and window buttons
    setWindowFlags(Qt::FramelessWindowHint);
    ui->lineEdit_User_Name->setFocus();
    setTabOrder(ui->lineEdit_User_Name, ui->lineEdit_Password);

    connect(ui->lineEdit_Password, &QLineEdit::returnPressed, ui->pushButton_Login, &QPushButton::click); // For the ENTER key when it's pressed while being selected on the linedit_password
    connect(ui->lineEdit_User_Name, &QLineEdit::returnPressed, ui->pushButton_Login, &QPushButton::click);
}

login_sign_up_in::~login_sign_up_in()
{
    delete ui;
}

bool emailCorrect=false; // Initialize boolean variables to check if email and password are correct
bool passwordCorrect=false;
void login_sign_up_in::on_pushButton_Login_clicked() // Function called when the "Login" button is clicked
{

    QString Username = ui->lineEdit_User_Name->text(); // Get the username and password entered by the user
    QString Password = ui->lineEdit_Password->text();
    //MANUAL OVERRIDE FOR DEBUG
    int i=0;
    // Check if the email entered by the user is correct
    for (const auto& email : myNamespace::emails) {

        std::string test = email.toStdString();
        if(test==Username.toStdString()){
            emailCorrect=true;
            username_change::pass_check_number=i;
        }
        i++;
    }
    int k=0; // Check if the password entered by the user is correct
    for (const auto& password : myNamespace::passwords) {

        std::string test_password = password.toStdString();
        if(test_password==Password.toStdString() && username_change::pass_check_number==k){
            passwordCorrect=true;
            std::cout << "Welcome back " << username_change::full_name[username_change::pass_check_number] << "!" << std::endl;
        }
        k++;
    }
    // Set the text of the username_label




        if(1){//<-------------------------------------------------
//    if(emailCorrect && passwordCorrect){// Open the main window if the email and password are correct
//    if(Username == "jim123" && Password == "123"){
        if(!mainwindow){
            mainwindow = new MainWindow();
        }
        this->hide();
        if(!mainwindow->isVisible()){ // Preventing the main window from opening 2 times with the press of the ENTER key.
            mainwindow->show();
        }
    }else{ // Display an error message if the email and password are not correct
        QMessageBox::warning(this,"Jim", "Enter correct info.");
    }
}


void login_sign_up_in::on_pushButton_Cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Jim", "Quit the application?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QApplication::quit();
    }
}
