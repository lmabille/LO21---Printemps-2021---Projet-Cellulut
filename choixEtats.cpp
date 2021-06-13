/**
 * @file chixEtats.cpp
 * @author Laurine Hamard/Thomas Guegan (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */



#include "choixEtats.h"
#include "informations.h"
#include <string>

/**
 * @brief constructeur de la fenêtre choixEtats
 *
 * @param[in] parent pointeur sur la fenêtre parente de celle que l'on construit,
 * @param[in] le voisinage que l'utilisateur a choisit précedemment
 * @param[in] la transition choisit par l'utilisateur
 * @return pas de type de retour
 */
ChoixEtats::ChoixEtats(QWidget* parent, Voisinage *v, std::string tr){


    //On récupère le nom de la transition
    transition=tr;

    //On initialise les layout et les éléments
    ensemble = new QVBoxLayout;



    titre = new QLabel("Choix des états");

        //Les layout


    ensemble->addWidget(titre);


    //On choisit un nombre d'état en fonction de la transition
    if (tr == "Game Of Life"){
       ee = new EnsembleEtats(2);


    }

    if (tr == "Brian's Brain"){
       ee = new EnsembleEtats(3);


    }

    if (tr == "Automate circulaire de Griffeath"){
       ee = new EnsembleEtats(4);


    }

    if (tr == "Langton's Loop"){
       ee = new EnsembleEtats(8);


    }


//On crée une zone pour choisir le label et la couleur pour chaque état

    for(int i=0; i<ee->getNombreEtats(); i++){

        ligneE[i] = new QHBoxLayout;
        labelE[i] = new QLineEdit;
        indiceE[i] = new QLabel();
        couleurE[i] = new ListeCouleur();

        indiceE[i]->setText(QString::number(i));

        ligneE[i]->addWidget(indiceE[i]);
        ligneE[i]->addWidget(labelE[i]);
        ligneE[i]->addWidget(couleurE[i]);




        ensemble->addLayout(ligneE[i]);
    }




    voi=v;

    valider = new QPushButton("valider");
    connect(valider,SIGNAL(clicked()),this,SLOT(Validation()));
    ensemble->addWidget(valider);

   setLayout(ensemble);


}


/**
 * @brief slot de sortie de la fenêtre, une fois que tous les états ont été choisis
 *
 * @param[in] pas de paramètre d'entrée
 * @return pas de type de retour
 */
void ChoixEtats::Validation(){

    //On initialise la liste d'états en fonction de ce qu'à entré l'utilisateur
    Etat *liste=ee->getListe();
    for(int i=0; i<ee->getNombreEtats(); i++){
        liste[i].setIndice(i);
        liste[i].setlabel(labelE[i]->text().toStdString());

       liste[i].setCouleur(couleurE[i]->currentText().toStdString());

    }

//On ouvre la fenêtre suivante qui permet de choisir les informations du modèle

   informations  * i;
   if (transition == "Langton's Loop") i = new informations(nullptr, transition, voi, ee, "extension");
   else i = new informations(nullptr, transition, voi, ee, "intension");

    i->show();
    this->close();




}


ListeCouleur::ListeCouleur() {
    this->addItem("blanc");
    this->addItem("noir");
    this->addItem("rouge");
    this->addItem("vert");
    this->addItem("bleu");
    this->addItem("jaune");
    this->addItem("magenta");
    this->addItem("rose");
    this->addItem("orange");
    this->addItem("peppermint");

}
