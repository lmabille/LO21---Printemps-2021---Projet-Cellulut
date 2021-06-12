#include "choixEtats.h"



ChoixEtats::ChoixEtats(QWidget* parent, Voisinage *v, std::string tr){


    ensemble = new QVBoxLayout;

    valider = new QPushButton("valider");
    connect(valider,SIGNAL(clicked()),this,SLOT(Validation()));

    titre = new QLabel("Choix des états");

        //Les layout


    ensemble->addWidget(titre);


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
std::cout<<ee->getNombreEtats();

    for(int i=0; i<ee->getNombreEtats(); i++){

        ligneE[i] = new QHBoxLayout;
        labelE[i] = new QLineEdit;
        indiceE[i] = new QLabel();
        indiceE[i]->setText(QString::number(i));

        ligneE[i]->addWidget(indiceE[i]);
        ligneE[i]->addWidget(labelE[i]);



        ensemble->addWidget(valider);
        ensemble->addLayout(ligneE[i]);
    }




    voi=v;


   setLayout(ensemble);


}

void ChoixEtats::Validation(){

    Etat *liste=ee->getListe();
    for(int i=0; i<ee->getNombreEtats(); i++){
        liste[i].setIndice(i);
        liste[i].setlabel(labelE[i]->text().toStdString());
       // liste[i].setCouleur(labelE[i]->text().toStdString()); je te laisse faire ça Thomas ;)

    }




}
