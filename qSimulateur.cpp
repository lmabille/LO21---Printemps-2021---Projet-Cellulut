#include <qSimulateur.h>

qSimulateur::qSimulateur(QWidget* parent, Modele *modele, Configuration *conf):QWidget(parent){

    //Création du simulateur




   S = new Simulateur(*modele, *conf);




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
           // grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 0, 255));
        }
    }

    //grille.show();

    //Boutons et layout

    ensemble = new QVBoxLayout;



    boutons = new QHBoxLayout;
    depart= new QPushButton("Revenir au début");
    play= new QPushButton("Lancer la simulation");
    pas= new QPushButton("Avancer d'un pas");
    save= new QPushButton("Enregistrer la configuration actuelle");
    boutons->addWidget(play);
    boutons->addWidget(depart);
    boutons->addWidget(pas);
    boutons->addWidget(save);

    //Gestion de la vitesse de lecture
    vitesse=new QSpinBox;
    vitesse->setRange(0,100);
    vitesse->setValue(0);
    vit = new QLabel("Vitesse de défilement (1= pas/par seconde)");
    gestionVitesse = new QHBoxLayout;
    gestionVitesse->addWidget(vit);
    gestionVitesse->addWidget(vitesse);


    ensemble->addWidget(grille);
    ensemble->addLayout(boutons);
    ensemble->addLayout(gestionVitesse);

    setLayout(ensemble);

}
