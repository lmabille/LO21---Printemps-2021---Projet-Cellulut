#include"choixTransition.h"
#include "ChoixVoisinage.h"
#include <QString>
#include <iostream>


choixTransition::choixTransition(QWidget* parent):QWidget(parent){

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

void choixTransition::SelectionTr(){

    auto current = choix->currentItem();
    transition = current->text().toStdString();
}

void choixTransition::Validation(){

   ChoixVoisinage  * c = new ChoixVoisinage(this, transition, 10, 10);
   c->show();
   this->close();




}
