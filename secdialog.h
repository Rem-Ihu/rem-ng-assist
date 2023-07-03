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

    void on_battery_clicked();

    void on_protec_error_clicked();

    void on_misc_button_clicked();

    void on_live_2_clicked();

    void on_live_signal_clicked();

    void on_battery_cell_clicked();

    void on_battery_charge_clicked();

    void on_battery_energy_clicked();

    void on_battery_live_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_average_cell_bal_clicked();

    void on_average_cell_module_clicked();

    void on_average_cell_voltage_clicked();

    void on_max_cell_bal_clicked();

    void on_max_cell_module_temp_clicked();

    void on_max_cell_voltage_clicked();

    void on_min_cell_balancing_clicked();

    void on_min_cell_module_temp_clicked();

    void on_min_cell_voltage_clicked();

    void on_live_msb_clicked();

    void on_live_lsb_clicked();

    void on_energy_charge_clicked();

    void on_energy_consumption_clicked();

    void on_energy_distance_clicked();

    void on_energy_es_energy_clicked();

    void on_charging_state_clicked();

    void on_charging_time_clicked();

    void on_battery_status_clicked();

    void on_battery_input_clicked();

    void on_battery_output_clicked();

    void on_battery_flags_clicked();

    void on_battery_charging_clicked();

    void on_battery_flags_2_clicked();

    void on_battery_input_2_clicked();

    void on_battery_input_5_clicked();

    void on_battery_input_3_clicked();

    void on_battery_input_4_clicked();

    void on_battery_input_7_clicked();

    void on_battery_input_6_clicked();

    void on_battery_input_9_clicked();

    void on_battery_input_8_clicked();

    void on_battery_input_13_clicked();

    void on_battery_input_10_clicked();

    void on_battery_input_11_clicked();

    void on_battery_input_14_clicked();

    void on_battery_input_12_clicked();

private:
    Ui::secDialog *ui;

};

#endif // SECDIALOG_H
