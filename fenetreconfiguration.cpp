    /**
 * @file fenetreconfiguration.cpp
 * @author Thomas Guegan (you@domain.com)
 * @brief fonctions de la classe FenetreConfiguration
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */



#include "fenetreconfiguration.h"
#include "ui_fenetreconfiguration.h"


/**
 * @brief Constructeur de la fenetre permettant la gestion des configurations
 *
 * @param[in] widget parent
 * @param[in] Pointeur sur le modèle chargé
 * @param[in] Instance du simulateur
 * @param[in] nom du fichier
 * @return fenetre graphique de gestion de configuration
 */

FenetreConfiguration::FenetreConfiguration(QWidget *parent, Modele * modele, Simulateur* simul, const char * nom ) :
    QDialog(parent),

    ui(new Ui::FenetreConfiguration),
    nom_fichier(nom),
    simul(simul),
    modele(modele)
{
    int nb = getNbConfig(this->nom_fichier);
    string * liste_config = new string[nb]();
    liste_config = getListeConfig(this->nom_fichier);

    auto res = Reseau(0,0);
    Configuration * conf = new  Configuration(res);
    this->simul->setConfigDepart(*conf);








    ui->setupUi(this);

    remplirComboList(liste_config,nb);
    initConnect();


}

/**
 * @brief Destructeur de la fenetre permettant la gestion des configurations
 *
 */
FenetreConfiguration::~FenetreConfiguration()
{
    delete ui;
}


/**
 * @brief fonction permettant de remplir la liste déroulante des noms de configurations
 *
 * @param[in] liste de nom de configuration
 * @param[in] nombre de configurations
 * @return void
 */
void FenetreConfiguration::remplirComboList(string * liste,int nb) {
    for (int i =0; i<nb; i++) {
        ui->comboBox->addItem(QString::fromStdString(liste[i]));
    }
}

/**
 * @brief Récupération du nom de configuration et chargement de celle-ci dans le simulateur
 * @return void
 */
void FenetreConfiguration::chargerConfig() {
    string nom =  ui->comboBox->currentText().toStdString();
    Configuration * config = chargerConfiguration(this->nom_fichier,nom);
    this->simul->setConfigDepart(*config);
    ui->label->setText(QString::fromStdString(nom));
    ui->label->show();
}

/**
 * @brief Initialisation du connect du bouton charger
 * @return void
 */
void FenetreConfiguration::initConnect() {
    connect(ui->btnCharger,SIGNAL(pressed()),this,SLOT(on_btnCharger_clicked()));
}


/**
 * @brief Fonction appelée lors du clic sur le bouton de chargement
 * @return void
 */
void FenetreConfiguration::on_btnCharger_clicked()
{

    chargerConfig();
    chargerPreview();


}


/**
 * @brief Affichage de la preview de la configuration dans la grille de la fenêtre
 * @return void
 */
void FenetreConfiguration::chargerPreview() {
    unsigned int taille = 5;//taille cellule

    const int nbLigne= this->simul->getConfigurationDepart()->getReseauLignes();
    const int nbColonne= this->simul->getConfigurationDepart()->getReseauColonnes();

    QTableWidget * grille = new QTableWidget(nbLigne, nbColonne);//ici on met la taille passée en argument
    grille->setFixedSize(400,300);//permet d'agrandir la fenetre en faire une fonction de la taille

    //On enlève les labels et les scrollbar
    grille->horizontalHeader()->setVisible(false);
    grille->verticalHeader()->setVisible(false);

    grille->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    grille->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i=0; i<nbLigne; i++ ){//pour chaque colonne
        for(int j=0; j<nbColonne; j++){//pour chaque ligne
            grille->setColumnWidth(j, taille);

            grille->setRowHeight(i, taille);
            grille->setItem(i, j, new QTableWidgetItem(""));
            //On récupère la couleur de l'état

            //On appplique les couleurs correspondantes
            string couleur = simul->getConfigurationDepart()->getEtatCellule (i, j).getCouleur();
            if(couleur == "noir")grille->item(i, j)->setData(Qt::BackgroundRole, QColor(0, 0, 0));
            if(couleur == "blanc")grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 255, 255));
            if(couleur == "rouge")grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 0, 0));
            if(couleur == "vert")grille->item(i, j)->setData(Qt::BackgroundRole, QColor(50, 255, 0));
            if(couleur == "bleu")grille->item(i, j)->setData(Qt::BackgroundRole, QColor(0, 0, 255));
            if(couleur == "jaune")grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 215, 50));
            if(couleur == "magenta")grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 0, 255));
            if(couleur == "rose")grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 150, 203));
            if(couleur == "orange")grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 130, 20));
            if(couleur == "peppermint")grille->item(i, j)->setData(Qt::BackgroundRole, QColor(187, 254, 190));


        }
    }

    QLayoutItem *item;
        while ((item = ui->LayoutPreview->takeAt(0)))
        {


            ui->LayoutPreview -> removeItem(item);
            delete item;
        }




    ui->LayoutPreview->addWidget(grille);



}


/**
 * @brief Appel de l'instance creer configuration
 * @return void
 */
void FenetreConfiguration::creerConfig() {
    CreaConfig * pageConfig = new CreaConfig(this,simul);
    pageConfig->show();

}

/**
 * @brief Fonction du slot du bouton creer
 * @return void
 */
void FenetreConfiguration::on_btnCreer_clicked()
{
    creerConfig();
}

/**
 * @brief Fonction du slot du bouton reload
 * @return void
 */
void FenetreConfiguration::on_btnReload_clicked()
{
    chargerPreview();
}

/**
 * @brief Fonction du slot du bouton valider
 * @return void
 */
void FenetreConfiguration::on_btnValider_clicked()
{
    qSimulateur* fenetre = new qSimulateur(nullptr, modele, simul->getConfigurationDepart());


    fenetre->show();
}



