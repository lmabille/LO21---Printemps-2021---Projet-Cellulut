#include "informations.h"
#include "ui_informations.h"

informations::informations(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::informations)
{
    ui->setupUi(this);
}

informations::~informations()
{
    delete ui;
}
