#ifndef CHOIXVOISINAGE_H
#define CHOIXVOISINAGE_H

#include "voisinage.h"
#include <stdlib.h>

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QIntValidator>
#include <QString>
#include <qboxlayout.h>
#include <QHeaderView>
#include <QModelIndex>

#include <QComboBox>
#include <QSpinBox>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

/*
class ChoixVonNeumann : public QWidget
{
    // Boutons
    Q_OBJECT
    QSpinBox* choixRayon;
public:
    explicit ChoixVonNeumann(QWidget* parent = nullptr); // à modifier
};
*/

class ChoixVoisinage : public QWidget
{
    // infos grille et cellule du milieu
    size_t dimSide = 3;
    size_t lineMiddleCell;
    size_t collumnMiddleCell;

    // Boutons
    Q_OBJECT
    QComboBox* listeVois;
    QSpinBox* choixRayon;
    QTableWidget* visu;
    QLabel* indication;
    QPushButton* validation;
    QPushButton* retour;
    QPushButton* appercu;

    // Layouts
    QHBoxLayout* parametres; // liste + indication
    QHBoxLayout* affichage; // visu + rayon
    QHBoxLayout* actions; // validation + retour
    QVBoxLayout* fenetre; // contient tous les autres layouts

public:
    // Constructeur
    size_t calculRayonMax(size_t nbLignesReseau, size_t nbLColonnesReseau);
    void calculDimSide (size_t rayonMax);
    void calculCoordMiddleCell () {lineMiddleCell = dimSide/2; collumnMiddleCell = dimSide/2;}
    size_t getDimSide() const {return dimSide;}
    int getLMiddCell() const {return lineMiddleCell;}
    int getCMiddCell() const {return collumnMiddleCell;}
    explicit ChoixVoisinage(QWidget* parent = nullptr, size_t nbLignesReseau = 3, size_t nbColonnesReseau = 3); // à modifier ensuite : on passe en argument les dimensions du réseaux choisies car donne les dimensions maximales du voisinage
    Voisinage* quelVoisinage(int i);
    void cleanAppercu();

private slots :
    void chargerAppercu();
    //void connexionVoisAppercu();



};

#endif // CHOIXVOISINAGE_H
