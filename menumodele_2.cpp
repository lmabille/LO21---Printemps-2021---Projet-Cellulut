#include "menumodele_2.h"
#include "ui_menumodele_2.h"

MenuModele_2::MenuModele_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuModele_2)
{
    ui->setupUi(this);
}

MenuModele_2::~MenuModele_2()
{
    delete ui;
}
