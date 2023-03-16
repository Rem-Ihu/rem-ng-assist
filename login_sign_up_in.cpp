#include "login_sign_up_in.h"
#include "ui_login_sign_up_in.h"
#include <QMainWindow>

login_sign_up_in::login_sign_up_in(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login_sign_up_in),
    mainwindow(nullptr)
{
    ui->setupUi(this);
    // remove title bar and window buttons
    setWindowFlags(Qt::FramelessWindowHint);
    ui->lineEdit_User_Name->setFocus();
    setTabOrder(ui->lineEdit_User_Name, ui->lineEdit_Password);

    connect(ui->lineEdit_Password, &QLineEdit::returnPressed, ui->pushButton_Login, &QPushButton::click); //for the ENTER key when it's pressed while being selected on the linedit_password


}

login_sign_up_in::~login_sign_up_in()
{
    delete ui;
}


void login_sign_up_in::on_pushButton_Login_clicked()
{

    QString Username = ui->lineEdit_User_Name->text();
    QString Password = ui->lineEdit_Password->text();
    //MANUAL OVERRIDE FOR DEBUG
    if(Username == "" && Password == ""){
    //if(Username == "jim123" && Password == "123"){
        if(!mainwindow){
            mainwindow = new MainWindow();
        }
        this->hide();
        if(!mainwindow->isVisible()){ //preventing the main window from opening 2 times with the press of the ENTER key.
            mainwindow->show();
        }
    }else{
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

