#ifndef MYCHARTWINDOW_H
#define MYCHARTWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QSplineSeries>
#include <QChart>
#include <QTimer>
#include <QCategoryAxis>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QChartView>

class MyChartWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyChartWindow(QWidget *parent = nullptr);

signals:

};

#endif // MYCHARTWINDOW_H
