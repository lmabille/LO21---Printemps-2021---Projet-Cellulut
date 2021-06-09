#ifndef QSIMULATEUR_H
#define QSIMULATEUR_H


#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QString>
#include <qboxlayout.h>
#include <QTableWidget>
#include <QHeaderView>
#include <QModelIndex>
#include <QPushButton>
#include "simulateur.h"

class qSimulateur : public QWidget
{

    Simulateur *S;

    //Pour lancer la config
    bool tourne = 0;

    QTimer *timer;



    //Boutons fenêtres
    Q_OBJECT
    QTableWidget *grille;
    QPushButton *depart;
    QPushButton *play;
    QPushButton *pas;
    QPushButton *save;
    QSpinBox *vitesse;
    QLabel *vit;

    //Les layout
    QHBoxLayout *boutons;
    QHBoxLayout *gestionVitesse;
    QVBoxLayout *ensemble;




public:
    // Constructeur
    explicit qSimulateur(QWidget* parent = nullptr, Modele *modele = nullptr, Configuration *conf =nullptr );

private slots:

    // Passer à la configuration suivante
    void configurationSuivante();

   //Sauvegarder la configuration courante
    //void choixNomConfig();
    void sauvegarderCC();

    //Lancer la simulation
    void LancerSim();
};




#endif // QSIMULATEUR_H
