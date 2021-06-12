#include <qSimulateur.h>
#include <iostream>
//#include <time.h>
//#include <dos.h>
//#include <windows.h>
#include <QTimer>

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


    ensemble->addWidget(grille);
    ensemble->addLayout(boutons);
    ensemble->addLayout(gestionVitesse);

    setLayout(ensemble);

}

void qSimulateur::configurationSuivante(){

  //  std::cout<<"bonjour !";
   // std::cout<<S->getLastConfig().getEtatCellule(0,0).getCouleur();
    S->next();
   // std::cout<<S->getLastConfig().getEtatCellule(0,0).getCouleur()<<"\n";
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

/*
void qSimulateur::choixNomConfig(){
    QVBoxLayout *fenetre = new QVBoxLayout;
    QLabel *annonce = new QLabel("Veuillez choisir le nom de cette configuration");


    setLayout(fenetre);
}

*/

void qSimulateur::sauvegarderCC(){


S->getLastConfig().sauvegarderConfiguration(S->modele.getTitre());
}


void qSimulateur::LancerSim(){
 if(tourne == 0)tourne=1;
    else tourne=0;
   // std::cout<<"Hey !";

    //std::cout<<"Hey 2!";
   if (tourne ==1){
        std::cout<<"Hey 3 !";
        timer->start(10000/vitesse->value());
      //  std::cout<<"Hey 4 !";
    }
    if(tourne == 0)timer->stop();




}

void qSimulateur::configInitiale(){

    S->reset();
    const int nbLigne= S->getLastConfig().getReseauLignes();
    const int nbColonne= S->getLastConfig().getReseauColonnes();
   // std::cout<<initiale->getEtatCellule(0, 0).getCouleur();
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

           // grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 0, 255));
        }
    }




}
