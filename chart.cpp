#include "chart.h"
#include "qchartview.h"
#include "qpainter.h"

Charts::Charts(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setupSmallChart();

}

Charts::~Charts()
{
    delete ui;
}

void Charts::setupBigOneChart()
{

}
