#include "choixEtats.h"
#include "informations.h"
#include <string>


ChoixEtats::ChoixEtats(QWidget* parent, Voisinage *v, std::string tr){

    transition=tr;
    ensemble = new QVBoxLayout;



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

void ChoixEtats::Validation(){

    Etat *liste=ee->getListe();
    for(int i=0; i<ee->getNombreEtats(); i++){
        liste[i].setIndice(i);
        liste[i].setlabel(labelE[i]->text().toStdString());

       liste[i].setCouleur(couleurE[i]->currentText().toStdString()); //je te laisse faire ça Thomas ;)

    }

    for(int i=0; i<ee->getNombreEtats(); i++){
        cout << liste[i].getIndice() <<"  ";
        cout << liste[i].getLabel() <<"  ";
        cout << liste[i].getCouleur() << endl;; //je te laisse faire ça Thomas ;)

    }

   informations  * i;
   if (transition == "Langton's Loop") i = new informations(nullptr, transition, voi, ee, "extension");
   else i = new informations(nullptr, transition, voi, ee, "intension");
   std::cout<<"ON EST LAAAA "<<transition;
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
