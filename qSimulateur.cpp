/**
 * @file qSimulateur.cpp
 * @author Laurine Hamard(you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */



#include <qSimulateur.h>
#include <iostream>
//#include <time.h>
//#include <dos.h>
//#include <windows.h>
#include <QTimer>


/**
 * @brief constructeur de la fenêtre qSimulateur
 *
 * @param[in] parent pointeur sur la fenêtre parente de celle que l'on construit,
 * @param[in] le modèle du simulateur
 * @param[in] la configuration initiale
 * @return pas de type de retour
 */
qSimulateur::qSimulateur(QWidget* parent, Modele *modele, Configuration *conf):QWidget(parent){

    //Création du simulateur




   S = new Simulateur(*modele, 1000);
   S->setConfigDepart(*conf);



    //Création de la grille

    unsigned int taille = 15;//taille cellule
    const int nbLigne= S->getConfigurationDepart()->getReseauLignes();
    const int nbColonne= S->getConfigurationDepart()->getReseauColonnes();
  // unsigned int nbLigne=15;
   //unsigned int nbColonne=20;
    grille = new QTableWidget(nbLigne, nbColonne);//ici on met la taille passé en argument
    grille->setFixedSize(2.61*taille*nbColonne, 1.61*taille*nbLigne);//permet d'agrandir la fenetre en faire une fonction de la taille

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
            string couleur = S->getConfigurationDepart()->getEtatCellule (i, j).getCouleur();
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
           // grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 0, 255));
         //   grille->item(i,j)->setText(QString::number(S->getLastConfig().getEtatCellule(i,j).getIndice()));
        }
    }

    //grille.show();

    //Boutons et layout

    ensemble = new QVBoxLayout;



    boutons = new QHBoxLayout;

    depart= new QPushButton("Revenir au début");
    connect(depart,SIGNAL(clicked()),this,SLOT(configInitiale()));

    play= new QPushButton("Lancer/Arrêter la simulation");
    connect(play,SIGNAL(clicked()),this,SLOT(LancerSim()));


    pas= new QPushButton("Avancer d'un pas");
    connect(pas,SIGNAL(clicked()),this,SLOT(configurationSuivante()));

    //On crée le qtimer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(configurationSuivante()));


    save= new QPushButton("Enregistrer la configuration actuelle");
    connect(save,SIGNAL(clicked()),this,SLOT(sauvegarderCC()));

    boutons->addWidget(play);
    boutons->addWidget(depart);
    boutons->addWidget(pas);
    boutons->addWidget(save);

    //Gestion de la vitesse de lecture
    vitesse=new QSpinBox;
    vitesse->setRange(1,100);
    vitesse->setValue(10);



    vit = new QLabel("Vitesse de défilement (1= pas/pour 10 secondes)");
    gestionVitesse = new QHBoxLayout;
    gestionVitesse->addWidget(vit);
    gestionVitesse->addWidget(vitesse);


    //gestion retour en arrière
    arriere = new QPushButton("Retour d'un pas");
    connect(arriere, SIGNAL(clicked()), this, SLOT(configurationPrecedente()));
    numArriere = new QLabel;
    numArriere->setText(QString::fromStdString(to_string(S->rang)));
    gestionVitesse->addWidget(arriere);
    gestionVitesse->addWidget(numArriere);




    ensemble->addWidget(grille);
    ensemble->addLayout(boutons);
    ensemble->addLayout(gestionVitesse);

    setLayout(ensemble);

}

/**
 * @brief permet d'avancer d'un pas dans les configurations
 *
 */
void qSimulateur::configurationSuivante(){

    //on appella la fonction next() du simulateur
    S->next();
    //on met à jour chaque case de la grille
    const int nbLigne= S->getLastConfig().getReseauLignes();
    const int nbColonne= S->getLastConfig().getReseauColonnes();
    for(int i=0; i<nbLigne; i++ ){//pour chaque colonne
        for(int j=0; j<nbColonne; j++){//pour chaque ligne

            string couleur = S->getLastConfig().getEtatCellule (i, j).getCouleur();
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
           // grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 0, 255));
          //  grille->item(i,j)->setText(QString::number(S->getLastConfig().getEtatCellule(i,j).getIndice()));
        }
    }


}



/**
 * @brief sauvegarde la configuration courante
 *
 */

void qSimulateur::sauvegarderCC(){


S->getLastConfig().sauvegarderConfiguration(S->modele.getTitre());
}

/**
 * @brief Lance la simulation en mode automatique ou l'arrête
 *
 */

void qSimulateur::LancerSim(){

    //appelle un timer dépedant de la vitesse quand tourne = 1
 if(tourne == 0)tourne=1;
    else tourne=0;

   if (tourne ==1){
        timer->start(10000/vitesse->value());
    }
    if(tourne == 0)timer->stop();




}

/**
 * @brief Permet de retourner à  la configuration initiale
 *
 */
void qSimulateur::configInitiale(){
    //va chercher la configuration initiale du simulateur et met à jour chaque case de la grille
    S->reset();
    const int nbLigne= S->getLastConfig().getReseauLignes();
    const int nbColonne= S->getLastConfig().getReseauColonnes();
   for(int i=0; i<nbLigne; i++ ){//pour chaque colonne
        for(int j=0; j<nbColonne; j++){//pour chaque ligne

            string couleur = S->getLastConfig().getEtatCellule(i, j).getCouleur();
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




}

/**
 * @brief Permet de retourner en arrière
 *
 */
void qSimulateur::configurationPrecedente(){
    if(S->rang == 0)return;
    S->rang--;

    const int nbLigne= S->getLastConfig().getReseauLignes();
    const int nbColonne= S->getLastConfig().getReseauColonnes();
   for(int i=0; i<nbLigne; i++ ){//pour chaque colonne
        for(int j=0; j<nbColonne; j++){//pour chaque ligne

            string couleur = S->getLastConfig().getEtatCellule(i, j).getCouleur();
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

    numArriere->setText(QString::fromStdString(to_string(S->rang)));



}
