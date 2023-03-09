#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void chartCreationSetup(int parses, std::vector<std::string> preferences_split, std::vector<QFrame*> frameArray);


private slots:
//    void on_pushButtonRTG_9_released();

//    void on_buttonFrame_customContextMenuRequested(const QPoint &pos);

//    void on_pushButtonHome_windowIconTextChanged(const QString &iconText);


    void on_pushButtonRealTimeData_clicked();

    void on_pushButtonCharts_clicked();

    void on_pushButton3DBikeView_clicked();

    void on_pushButtonNews_clicked();

    void on_pushButtonMerch_clicked();

    void on_pushButtonSettings_clicked();

    void on_pushButtonOthers_clicked();

    void on_pushButtonHome_clicked();

    void on_tabChartWidget_tabCloseRequested(int index);

    void on_addTabNameButton_clicked();

    void on_pushButtonAboutUs_clicked();

    void on_pushButtonContact_clicked();

    void on_pushButtonErrorPopUp_clicked();

    void create_chart(std::vector<QFrame*> frameArray, int parses);



private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
    QSplitter *splitter;


};
#endif // MAINWINDOW_H
