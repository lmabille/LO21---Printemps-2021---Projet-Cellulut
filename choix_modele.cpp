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

void Choix_Modele::recupModele(QListWidgetItem* QI){
    auto M = new Modele;
    auto txt = new QString("C:\\Users\\hocin\\Desktop\\LO21\\LO21---Printemps-2021---Projet-Cellulut\\Modeles\\");
    txt->append(QI->text()); //on créer une variable donnant le chemin d'accès au fichier XML
    auto NomDuFichier = new QByteArray (txt->toUtf8()); //pour convertir notre QString en char*
    M=chargerModel(NomDuFichier->constData()); //on charge le modèle choisi
    auto S = new Simulateur(*M);
    auto fenetre = new FenetreConfiguration(nullptr, M,S, NomDuFichier->constData()); //on charge les config
    fenetre->show();
    this->close();
}
