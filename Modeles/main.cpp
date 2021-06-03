#include<QApplication>
#include<QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QWidget>
#include <QColor>
#include <qboxlayout.h>
#include <QHeaderView>
#include <QModelIndex>
#include <QLayout>
#include <QSpinBox>
#include <QLabel>

int main(int argc, char * argv[]){
    QApplication app(argc, argv);
    QWidget fenetre;
    fenetre.setFixedSize(700, 500);

    //Création de la grille

    unsigned int taille = 15;//taille cellule
    QTableWidget grille(10, 10);//ici on met la taille passé en argument
    grille.setFixedSize(2.61*taille*10, 1.61*taille*10);//permet d'agrandir la fenetre en faire une fonction de la taille

    //On enlève les labels et les scrollbar
    grille.horizontalHeader()->setVisible(false);
    grille.verticalHeader()->setVisible(false);
    grille.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    grille.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(unsigned int i=0; i<10; i++ ){//pour chaque colonne
        for(unsigned int j=0; j<10; j++){//pour chaque ligne
            grille.setColumnWidth(i, taille);
            grille.setRowHeight(j, taille);
            grille.setItem(i, j, new QTableWidgetItem(""));
            //il faudrait qu'on récupère la couleur en fct de (i,j)
            grille.item(i, j)->setData(Qt::BackgroundRole, QColor(255, 0, 255));
        }
    }

    //grille.show();

    //Boutons et layout

    QVBoxLayout *ensemble = new QVBoxLayout;



    QHBoxLayout *boutons = new QHBoxLayout;
    QPushButton *depart= new QPushButton("Revenir au début");
    QPushButton *play= new QPushButton("Lancer la simulation");
    QPushButton *pas= new QPushButton("Avancer d'un pas");
    QPushButton *save= new QPushButton("Enregistrer la configuration actuelle");
    boutons->addWidget(play);
    boutons->addWidget(depart);
    boutons->addWidget(pas);
    boutons->addWidget(save);

    //Gestion de la vitesse de lecture
    QSpinBox *vitesse=new QSpinBox;
    vitesse->setRange(0,100);
    vitesse->setValue(0);
    QLabel *vit = new QLabel("Vitesse de défilement (1=10 pas par seconde)");
    QHBoxLayout *gestionVitesse = new QHBoxLayout;
    gestionVitesse->addWidget(vit);
    gestionVitesse->addWidget(vitesse);


    ensemble->addWidget(&grille);
    ensemble->addLayout(boutons);
    ensemble->addLayout(gestionVitesse);
    fenetre.setLayout(ensemble);
    fenetre.show();

    return app.exec();


}
