#include "menu_config.h"
#include "ui_menu_config.h"

menu_config::menu_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu_config)
{
    ui->setupUi(this);
}

menu_config::~menu_config()
{
    delete ui;
}
