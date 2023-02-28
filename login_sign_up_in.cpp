#include "login_sign_up_in.h"
#include "ui_login_sign_up_in.h"
#include <QMainWindow>

login_sign_up_in::login_sign_up_in(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login_sign_up_in)
{
    ui->setupUi(this);
    // remove title bar and window buttons
    setWindowFlags(Qt::FramelessWindowHint);

}

login_sign_up_in::~login_sign_up_in()
{
    delete ui;
}

void login_sign_up_in::on_pushButton_Login_clicked()
{
    QString Username = ui->lineEdit_User_Name->text();
    QString Password = ui->lineEdit_Password->text();
    if(Username == "jim123" && Password == "123"){
        QMessageBox::information(this,"Jim", "Login success.");
        this->hide();
        MainWindow *mainwindow = new MainWindow();
        mainwindow->show();
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

