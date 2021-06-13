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
    //std::cout<<"yo"<<current->text().toStdString();
    transition = current->text().toStdString();

    std::cout << "selection : " << transition << endl;



}

void choixTransition::Validation(){

   ChoixVoisinage  * c = new ChoixVoisinage(nullptr, transition, 10, 10);
   std::cout << "validation choix transition : " << transition << endl;
   //c->setTransition(transition);

   c->show();
   this->close();




}
