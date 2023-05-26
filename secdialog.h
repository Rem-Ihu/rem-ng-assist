#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QWidget>
#include <QDialog>
namespace Ui {
class secDialog;
}

class secDialog : public QWidget
{
    Q_OBJECT

public:
    explicit secDialog(QWidget *parent = nullptr);
    ~secDialog();
    void setModal(bool modal); // function declaration
private slots:

    void on_cell_clicked();

    void on_charge_clicked();

    void on_battery_clicked();

    void on_energy_clicked();

    void on_live_clicked();

    void on_battery_error_clicked();

    void on_protec_error_clicked();

    void on_misc_button_clicked();

private:
    Ui::secDialog *ui;

};

#endif // SECDIALOG_H
