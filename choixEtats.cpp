#include "choixEtats.h"



choixEtats::choixEtats(QWidget* parent, Voisinage *v, std::string tr){


    if (tr == "Game Of Life"){
        indicesE = new QTableWidget(2, 1);
        for(int i=0; i<2; i++ ){//pour chaque colonne

                indicesE->setColumnWidth(1, 15);

                indicesE->setItem(i, 1, new QTableWidgetItem(i));//ou set text à tester
                //On récupère la couleur de l'état


               // grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 0, 255));
             //   grille->item(i,j)->setText(QString::number(S->getLastConfig().getEtatCellule(i,j).getIndice()));

        }

    }

    voi=v;

   valider = new QPushButton("valider");
   //connect(valider,SIGNAL(clicked()),this,SLOT(Validation()));

   titre = new QLabel("Choix des états");

       //Les layout


   ensemble = new QVBoxLayout;
   ensemble->addWidget(titre);
   ensemble->addWidget(valider);



}
