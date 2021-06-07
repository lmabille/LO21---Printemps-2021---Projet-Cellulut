#include "simu.h"
#include "ui_simu.h"

simu::simu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::simu)
{
    ui->setupUi(this);
}

simu::~simu()
{
    delete ui;
}
