#ifndef CHARTS_H
#define CHARTS_H

#include <QMainWindow>
#include <QSplineSeries>
#include <QChart>
#include <QTimer>
#include <QTime>
#include <QCategoryAxis>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include "./ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

namespace myNamespace{
    extern float fin_ans,sec_ans,ok;
}

class Charts : public QMainWindow
{
    Q_OBJECT

public:
    explicit Charts(QWidget *parent = nullptr);
    ~Charts();

private:
    Ui::MainWindow *ui;

    void setupBigOneChart();
    void setupSmallChart();

};

#endif // CHARTS_H
