/**
 * @file creaconfig.cpp
 * @author Thomas Guegan (you@domain.com)
 * @brief fonctions de la classe CreaConfig
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */


#include "creaconfig.h"
#include "ui_creaconfig.h"

QTextStream& qStdOut();



/**
 * @brief Constructueur de la fenetre de creation de configuration
 *
 * @param[in] widget parent
 * @param[in] instance du simulateur
 */
CreaConfig::CreaConfig(QWidget *parent, Simulateur * simu) :
    QDialog(parent),
    ui(new Ui::CreaConfig),
    simu(simu)
{





    ui->setupUi(this);
    ui->btnRandom->setDisabled(true); // on empeche de cliquer sur la generation de config random tant que le taille n'est pas définie

    on_btnReload_clicked();




}

/**
 * @brief Destructueur de la fenetre de creation de configuration
 */
CreaConfig::~CreaConfig()
{
    delete ui;
}


/**
 * @brief Slot du bouton de validation de la taille
 */
void CreaConfig::on_btnTaille_clicked()
{
    clearLayout(ui->LayoutGrille->layout());
    int ligne,colonne;
    ligne = ui->spinLigne->value();
    colonne = ui->spinColonne->value();
    this->res = new Reseau(ligne,colonne);

    Configuration * config = new Configuration(*res);

    for (int i = 0; i< ligne; i ++){
        for (int j = 0; j < colonne ; j++) {
            config->setEtatCellule(i,j,&simu->getModele()->getEtatsPossibles()->getListe()[0]);
        }
    }

    config_cour = config;

    this->simu->setConfigDepart(*config);


    chargerGrille();
    ui->btnRandom->setDisabled(false);
    //ui->btnTaille->setDisabled(true);

}

/**
 * @brief Chargement de la grille de bouton pour définition de la configuration
 */
void CreaConfig::chargerGrille() {


    const int nbLigne= this->simu->getConfigurationDepart()->getReseauLignes();
    const int nbColonne= this->simu->getConfigurationDepart()->getReseauColonnes();


        QGridLayout * grid = new QGridLayout(this);

        grid->maximumSize().setHeight(500);
        grid->maximumSize().setWidth(500);
        grid->setContentsMargins(0,0,0,0);
        grid->setSpacing(0);

        this->config_cour = simu->getConfigurationDepart();

        for(int i = 0; i < nbColonne; i++)
        {
            for(int j = 0; j < nbLigne; j++)
            {
                QPushButton * button = new QPushButton();
                button->setFixedSize(30,30);
                grid->addWidget(button, j, i);


                button->setText(QString::number(simu->getConfigurationDepart()->getEtatCellule(j,i).getIndice()));


                string couleur = simu->getConfigurationDepart()->getEtatCellule(j,i).getCouleur();

                if(couleur == "noir")button->setStyleSheet("background-color : rgb(0, 0, 0)");
                if(couleur == "blanc")button->setStyleSheet("background-color : rgb(255, 255, 255)"); // (255, 255, 255));
                if(couleur == "rouge")button->setStyleSheet("background-color : rgb(255, 0, 0)");//(255, 0, 0));
                if(couleur == "vert")button->setStyleSheet("background-color : rgb(50, 255, 0)"); //(50, 255, 0));
                if(couleur == "bleu")button->setStyleSheet("background-color : rgb(0, 0, 255)"); //(0, 0, 255));
                if(couleur == "jaune")button->setStyleSheet("background-color : rgb(255, 215, 50)"); //(255, 215, 50));
                if(couleur == "magenta")button->setStyleSheet("background-color : rgb(255, 0, 255)"); // (255, 0, 255));
                if(couleur == "rose")button->setStyleSheet("background-color : rgb(255, 150, 203)"); //(255, 150, 203));
                if(couleur == "orange")button->setStyleSheet("background-color : rgb(255, 130, 20)");// (255, 130, 20));
                if(couleur == "peppermint")button->setStyleSheet("background-color : rgb(148, 255, 216)"); //(187, 254, 190));



                connect(button, &QPushButton::clicked, [=](){

                    changeEtat(i,j,this->config_cour,button);
                });
            }



    ui->LayoutGrille->setLayout(grid);
}


}

/**
 * @brief Clear des éléments d'un layout
 *
 * @param[in] layout à vider
 */
void CreaConfig::clearLayout(QLayout* layout) {
    QWidget().setLayout(layout);
}


/**
 * @brief Changement d'états d'une cellule selon un cycle  ex : 0 -> 1 -> 2 -> 0 ...
 *
 * @param[in] ligne
 * @param[in] colonne
 * @param[in] configuration en cour
 * @param[in] pointeur sur le bouton correspondant à la cellule
 */
void CreaConfig::changeEtat(int j,int i,Configuration* config, QPushButton* button) {
    int indice = config->getEtatCellule(i,j).getIndice();


    if (indice == simu->getModele()->getEtatsPossibles()->getNombreEtats()-1)
        indice = 0;
    else
        indice +=1;
    config->setEtatCellule(i,j,&simu->getModele()->getEtatsPossibles()->getListe()[indice]);



    string couleur = config->getEtatCellule (i, j).getCouleur();
    if(couleur == "noir")button->setStyleSheet("background-color : rgb(0, 0, 0)");
    if(couleur == "blanc")button->setStyleSheet("background-color : rgb(255, 255, 255)");// (255, 255, 255));
    if(couleur == "rouge")button->setStyleSheet("background-color : rgb(255, 0, 0)");//(255, 0, 0));
    if(couleur == "vert")button->setStyleSheet("background-color : rgb(50, 255, 0)"); //(50, 255, 0));
    if(couleur == "bleu")button->setStyleSheet("background-color : rgb(0, 0, 255)"); //(0, 0, 255));
    if(couleur == "jaune")button->setStyleSheet("background-color : rgb(255, 215, 50)"); //(255, 215, 50));
    if(couleur == "magenta")button->setStyleSheet("background-color : rgb(255, 0, 255)"); // (255, 0, 255));
    if(couleur == "rose")button->setStyleSheet("background-color : rgb(255, 150, 203)"); //(255, 150, 203));
    if(couleur == "orange")button->setStyleSheet("background-color : rgb(255, 130, 20)");// (255, 130, 20));
    if(couleur == "peppermint")button->setStyleSheet("background-color : rgb(148, 255, 216)"); //(187, 254, 190));



    button->setText(QString::number(indice));



    this->simu->setConfigDepart(*config);

}


QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}


/**
 * @brief Slot du bouton random
 */
void CreaConfig::on_btnRandom_clicked()
{
    this->simu->getConfigurationDepart()->remplissageAleatoire(*this->simu->getModele()->getEtatsPossibles());
    on_btnReload_clicked();
    //close();



}
/**
 * @brief Slot du bouton reload
 */
void CreaConfig::on_btnReload_clicked()
{
    //ui->btnTaille->setDisabled(true);
    clearLayout(ui->LayoutGrille->layout());
    //QWidget().setLayout(ui->LayoutGrille->layout());

    chargerGrille();
}
