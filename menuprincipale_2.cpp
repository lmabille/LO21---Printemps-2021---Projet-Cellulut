#include "menuprincipale_2.h"
#include "ui_menuprincipale_2.h"

MenuPrincipale_2::MenuPrincipale_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuPrincipale_2)
{
    ui->setupUi(this);
}

MenuPrincipale_2::~MenuPrincipale_2()
{
    delete ui;
}
