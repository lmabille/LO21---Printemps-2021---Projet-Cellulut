#include "choix_modele.h"
#include "ui_choix_modele.h"

Choix_Modele::Choix_Modele(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Choix_Modele)
{
    ui->setupUi(this);
}

Choix_Modele::~Choix_Modele()
{
    delete ui;
}
