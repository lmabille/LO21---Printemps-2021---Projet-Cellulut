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

class qSimulateur : public QWidget
{

    //Simulateur S;


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
    explicit qSimulateur(QWidget* parent = nullptr);

private slots:
    /*
    // Question 1 - Interface de configuration de l'automate
    void synchronizeNumToNumBit(int i);
    void synchronizeNumBitToNum(const QString& s);

    // Question 2 - Interface de configuration de l'etat de départ
    void cellActivation(const QModelIndex& index);

    // Question 3 - Interface d'affichage des états générés
    void faireSimulation();*/
};




#endif // QSIMULATEUR_H
