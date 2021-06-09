#include "creaconfig.h"
#include "ui_creaconfig.h"

CreaConfig::CreaConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreaConfig)
{
    ui->setupUi(this);
}

CreaConfig::~CreaConfig()
{
    delete ui;
}
