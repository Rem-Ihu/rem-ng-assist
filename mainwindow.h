#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCharts>
#include<QChartView>
#include<QLineSeries>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



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

    void on_pushButtonHome_clicked();

    void on_tabChartWidget_tabCloseRequested(int index);

    void on_addTabNameButton_clicked();

    void on_pushButtonAboutUs_clicked();

    void on_pushButtonContact_clicked();

    void on_pushButtonErrorPopUp_clicked();



    void on_displaybutton_clicked();

    void on_historybutton_clicked();

    void on_measurementsbutton_clicked();

    void on_accountbutton_clicked();

    void on_defaultblackblue_clicked();

    void on_bluepink_clicked();

    void on_whiteblack_clicked();

    void on_blackpurple_clicked();

    void on_blackred_clicked();

    void on_resolutionslider_valueChanged(int value);


    void on_chart1buttonhistory_clicked();

    void on_chart2buttonhistory_clicked();

    void on_chart3buttonhistory_clicked();

    void on_chart4buttonhistory_clicked();

    void on_chart5buttonhistory_clicked();

    void on_chart6buttonhistory_clicked();

    void on_chart7buttonhistory_clicked();

    void on_IconButton_clicked();

    void on_password_button_clicked();

    void on_username_button_clicked();

    void on_go_back_user_clicked();

    void on_go_back_passw_clicked();

    void on_color_change_button_clicked();

    void on_greenblack_clicked();

private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
    QSplitter *splitter;

};
#endif // MAINWINDOW_H
