/**
 * @file choixTransition.cpp
 * @author Laurine Hamard(you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */




#include"choixTransition.h"
#include "ChoixVoisinage.h"
#include <QString>
#include <iostream>



/**
 * @brief constructeur de la fenêtre choixTransition
 *
 * @param[in] parent pointeur sur la fenêtre parente de celle que l'on construit
 * @return pas de type de retour
 */
choixTransition::choixTransition(QWidget* parent):QWidget(parent){

    //Création de la liste des transition et des layout et des boutons de validations
    choix = new QListWidget;
    choix->addItem("Game Of Life");

    choix->addItem("Brian's Brain");

    choix->addItem("Automate circulaire de Griffeath");

    choix->addItem("Langton's Loop");

    connect(choix,SIGNAL(itemSelectionChanged()),this,SLOT(SelectionTr()));


    valider = new QPushButton("valider");
    connect(valider,SIGNAL(clicked()),this,SLOT(Validation()));

    titre = new QLabel("Choix de la transitiion");

        //Les layout


    ensemble = new QVBoxLayout;
    ensemble->addWidget(titre);
    ensemble->addWidget(choix);
    ensemble->addWidget(valider);

    setLayout(ensemble);


}



/**
 * @brief Change le nom de la transition par l'objet selectionné par l'utilisateur
 *
 * @param[in] pas de paramètre d'entrée
 * @return pas de type de retour
 */

void choixTransition::SelectionTr(){

    auto current = choix->currentItem();
    //std::cout<<"yo"<<current->text().toStdString();
    transition = current->text().toStdString();




}

/**
 * @brief slot de sortie de la fenêtre, vers le choix de voisinage
 *
 * @param[in] pas de paramètre d'entrée
 * @return pas de type de retour
 */


void choixTransition::Validation(){

   ChoixVoisinage  * c = new ChoixVoisinage(nullptr, transition, 10, 10);
   std::cout << "validation choix transition : " << transition << endl;
   //c->setTransition(transition);

   c->show();
   this->close();




}
