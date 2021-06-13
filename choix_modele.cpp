/**
 * @file choix_modele.cpp
 * @author Orhane Lahneche (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "choix_modele.h"
#include "ui_choix_modele.h"


/**
 * @brief constructeur de la fenêtre choix_modele
 *
 * @param[in] parent pointeur sur la fenêtre parente de celle que l'on construit
 * @return caractère correspondant à l'état de la cellule à la génération t+1
 */
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

/**
 * @brief destructeur de la fenêtre choic_model
 */
Choix_Modele::~Choix_Modele()
{
    delete ui;
}

/**
 * @brief chargement du modèle après le choix de l'utilisateur
 *
 * @param[in] QI Item de la liste qui est double-cliqué
 * @return ferme la fenetre de choix du modèle et ouvre la fenetre du choix de la configuration
 */
void Choix_Modele::recupModele(QListWidgetItem* QI){
    auto M = new Modele;
    auto txt = new QString("..\\LO21---Printemps-2021---Projet-Cellulut\\Modeles\\");
    txt->append(QI->text()); //on créer une variable donnant le chemin d'accès au fichier XML
    auto NomDuFichier = new QByteArray (txt->toUtf8()); //pour convertir notre QString en char*
    M=chargerModel(NomDuFichier->constData()); //on charge le modèle choisi
    auto S = new Simulateur(*M);
    auto fenetre = new FenetreConfiguration(nullptr, M,S, NomDuFichier->constData()); //on charge les config
    fenetre->show();
    this->close();
}
