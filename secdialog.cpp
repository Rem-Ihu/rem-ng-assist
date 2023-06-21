#include "secdialog.h"
#include "ui_secdialog.h"

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

