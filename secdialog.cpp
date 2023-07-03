#include "secdialog.h"
#include "ui_secdialog.h"

namespace _RealTime{
    extern bool setRealTime;
    extern QString nameSetRealTime;
}

secDialog::secDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::secDialog)
{
    ui->setupUi(this);
}

secDialog::~secDialog()
{
    delete ui;
}
void secDialog::setModal(bool modal)
{
    setWindowModality(modal ? Qt::WindowModal : Qt::NonModal);
}

void secDialog::on_battery_clicked()
{
    ui->main_stacked->setCurrentIndex(0);
}

void secDialog::on_protec_error_clicked()
{
    ui->main_stacked->setCurrentIndex(2);
}

void secDialog::on_misc_button_clicked()
{
        ui->main_stacked->setCurrentIndex(1);
}

void secDialog::on_live_2_clicked()
{
    ui->main_stacked->setCurrentIndex(4);
}

void secDialog::on_live_signal_clicked()
{
         ui->main_stacked->setCurrentIndex(3);
}


void secDialog::on_battery_cell_clicked()
{
   ui->main_stacked->setCurrentIndex(2);
}


void secDialog::on_battery_charge_clicked()
{
   ui->main_stacked->setCurrentIndex(1);
}


void secDialog::on_battery_energy_clicked()
{
    ui->main_stacked->setCurrentIndex(0);
}


void secDialog::on_battery_live_clicked()
{
       ui->main_stacked->setCurrentIndex(4);
}


void secDialog::on_pushButton_clicked()
{
       ui->main_stacked->setCurrentIndex(3);
}


void secDialog::on_pushButton_3_clicked()
{
           ui->main_stacked->setCurrentIndex(3);
}


void secDialog::on_pushButton_4_clicked()
{
           ui->main_stacked->setCurrentIndex(3);
}


void secDialog::on_pushButton_5_clicked()
{
           ui->main_stacked->setCurrentIndex(3);
}


void secDialog::on_average_cell_bal_clicked()
{
    _RealTime::nameSetRealTime = "AV_CELL_BALANCING";
    _RealTime::setRealTime = true;
}


void secDialog::on_average_cell_module_clicked()
{
    _RealTime::nameSetRealTime = "AV_CELL_MODULE_TEMP";
    _RealTime::setRealTime = true;
}


void secDialog::on_average_cell_voltage_clicked()
{
    _RealTime::nameSetRealTime = "AV_CELL_VOLTAGE";
    _RealTime::setRealTime = true;
}


void secDialog::on_max_cell_bal_clicked()
{
    _RealTime::nameSetRealTime = "MAX_CELL_BALANCING";
    _RealTime::setRealTime = true;
}


void secDialog::on_max_cell_module_temp_clicked()
{
    _RealTime::nameSetRealTime = "MAX_CELL_MODULE_TEMP";
    _RealTime::setRealTime = true;
}


void secDialog::on_max_cell_voltage_clicked()
{
    _RealTime::nameSetRealTime = "MAX_CELL_VOLTAGE";
    _RealTime::setRealTime = true;
}


void secDialog::on_min_cell_balancing_clicked()
{
    _RealTime::nameSetRealTime = "MIN_CELL_BALANCING";
    _RealTime::setRealTime = true;
}


void secDialog::on_min_cell_module_temp_clicked()
{
    _RealTime::nameSetRealTime = "MIN_CELL_MODULE_TEMP";
    _RealTime::setRealTime = true;
}


void secDialog::on_min_cell_voltage_clicked()
{
    _RealTime::nameSetRealTime = "MIN_CELL_VOLTAGE";
    _RealTime::setRealTime = true;
}


void secDialog::on_live_msb_clicked()
{
    _RealTime::nameSetRealTime = "NO_OF_LIVE_CELLS_MSB";
    _RealTime::setRealTime = true;
}


void secDialog::on_live_lsb_clicked()
{
    _RealTime::nameSetRealTime = "NO_OF_LIVE_CELLS_LSB";
    _RealTime::setRealTime = true;
}


void secDialog::on_energy_charge_clicked()
{
    _RealTime::nameSetRealTime = "EST_CHARGE";
    _RealTime::setRealTime = true;
}


void secDialog::on_energy_consumption_clicked()
{
    _RealTime::nameSetRealTime = "EST_CONSUMPTION";
    _RealTime::setRealTime = true;
}


void secDialog::on_energy_distance_clicked()
{
    _RealTime::nameSetRealTime = "EST_DISTANCE_LEFT";
    _RealTime::setRealTime = true;
}


void secDialog::on_energy_es_energy_clicked()
{
    _RealTime::nameSetRealTime = "EST_ENERGY";
    _RealTime::setRealTime = true;
}


void secDialog::on_charging_state_clicked()
{
    _RealTime::nameSetRealTime = "CHARGING_STATE_DURATION";
    _RealTime::setRealTime = true;
}


void secDialog::on_charging_time_clicked()
{
    _RealTime::nameSetRealTime = "CHARGING_TIME";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_status_clicked()
{
    _RealTime::nameSetRealTime = "BATTERY_STATUS_FLAGS";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_clicked()
{
    _RealTime::nameSetRealTime = "INPUT_SIGNALS";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_output_clicked()
{
    _RealTime::nameSetRealTime = "OUTPUT_SIGNALS";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_flags_clicked()
{
    _RealTime::nameSetRealTime = "PROT_FLAGS_LSB";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_charging_clicked()
{
    _RealTime::nameSetRealTime = "LAST_CHARGING_ERROR";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_flags_2_clicked()
{
    _RealTime::nameSetRealTime = "NO_OF_LIVE_CELLS_MSB";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_2_clicked()
{
    _RealTime::nameSetRealTime = "TEMP_MOTOR";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_5_clicked()
{
    _RealTime::nameSetRealTime = "TEMP_MOTOR_EST";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_3_clicked()
{
    _RealTime::nameSetRealTime = "TEMP_MOTOR_MAX";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_4_clicked()
{
    _RealTime::nameSetRealTime = "TEMP_SEVCON";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_7_clicked()
{
    _RealTime::nameSetRealTime = "THROTTLE";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_6_clicked()
{
    _RealTime::nameSetRealTime = "TORQUE";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_9_clicked()
{
    _RealTime::nameSetRealTime = "TORQUE_MAX";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_8_clicked()
{
    _RealTime::nameSetRealTime = "TORQUE_TARG";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_13_clicked()
{
    _RealTime::nameSetRealTime = "TOTAL_VOLTAGE";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_10_clicked()
{
    _RealTime::nameSetRealTime = "VELOCITY";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_11_clicked()
{
    _RealTime::nameSetRealTime = "VELOCITY_ACT";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_14_clicked()
{
    _RealTime::nameSetRealTime = "VELOCITY_BATT";
    _RealTime::setRealTime = true;
}


void secDialog::on_battery_input_12_clicked()
{
    _RealTime::nameSetRealTime = "CURRENT_BATT";
    _RealTime::setRealTime = true;
}

