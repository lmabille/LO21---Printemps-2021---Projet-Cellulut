#include "taille_reseau.h"
#include "ui_taille_reseau.h"

taille_reseau::taille_reseau(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taille_reseau)
{
    ui->setupUi(this);
}

taille_reseau::~taille_reseau()
{
    delete ui;
}
