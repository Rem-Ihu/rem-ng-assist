#ifndef LOGIN_SIGN_UP_IN_H
#define LOGIN_SIGN_UP_IN_H

#include "qmainwindow.h"
#include "mainwindow.h"
#include <QDialog>
#include <QMessageBox>
#include <QMainWindow>

namespace Ui {

class login_sign_up_in;
}

class login_sign_up_in : public QMainWindow
{
    Q_OBJECT


public:
    explicit login_sign_up_in(QWidget *parent = nullptr);
    ~login_sign_up_in();

private slots:
    void on_pushButton_Login_clicked();
    void on_pushButton_Cancel_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::login_sign_up_in *ui;
    MainWindow *mainwindow;
};


#endif // LOGIN_SIGN_UP_IN_H
