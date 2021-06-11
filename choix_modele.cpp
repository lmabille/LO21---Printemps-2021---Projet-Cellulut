#include "choix_modele.h"
#include "ui_choix_modele.h"

Choix_Modele::Choix_Modele(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Choix_Modele)
{
    ui->setupUi(this);
    QDir dir("../LO21---Printemps-2021---Projet-Cellulut/Modeles");
    QStringList filters;
    filters << "*.xml";
    dir.setNameFilters(filters);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        ui->listWidget_2->addItem(fileInfo.fileName());
    }
}

Choix_Modele::~Choix_Modele()
{
    delete ui;
}

void Choix_Modele::recupModele(){
    //auto fenetre = new FenetreConfiguration;
    //fenetre->show();
    this->close();
}
