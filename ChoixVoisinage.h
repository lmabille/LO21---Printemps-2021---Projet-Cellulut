#ifndef CHOIXVOISINAGE_H
#define CHOIXVOISINAGE_H

#include "voisinage.h"
#include "Modele.h"

#include <vector>
#include <algorithm>

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


class ChoixVoisinage : public QWidget
{
    Modele* modele;

    // infos grille et cellule du milieu
    size_t rayonMax = 1;
    // size_t dimSide = 3;
    size_t lineMiddleCell;
    size_t collumnMiddleCell;

    Voisinage* choice;

    // Boutons
    Q_OBJECT
    QComboBox* listeVois;
    QSpinBox* choixRayon;
    QTableWidget* visu;
    QLabel* indication;
    QPushButton* validation;
    QPushButton* retour;
    QPushButton* appercu;
    QGridLayout* grid;

    // Layouts
    QHBoxLayout* parametres; // liste + indication
    QHBoxLayout* affichage; // visu + rayon
    QHBoxLayout* actions; // validation + retour
    QVBoxLayout* fenetre; // contient tous les autres layouts

public:
    // Constructeur
    void setRayonMax(size_t nbLignesReseau, size_t nbLColonnesReseau);
    size_t calculDimSide (size_t rayonMax);
    void calculCoordMiddleCell () {size_t dimSide = calculDimSide(rayonMax); lineMiddleCell = dimSide/2; collumnMiddleCell = dimSide/2;}
    int getLMiddCell() const {return lineMiddleCell;}
    int getCMiddCell() const {return collumnMiddleCell;}
    explicit ChoixVoisinage(QWidget* parent = nullptr, size_t nbLignesReseau = 3, size_t nbColonnesReseau = 3); // à modifier ensuite : on passe en argument les dimensions du réseaux choisies car donne les dimensions maximales du voisinage
    void quelVoisinage(int index, size_t rayonChoisi);
    void cleanAppercu();
    void creaGridShowOnly(size_t dimSide, size_t tailleCell);

private slots :
    void chargerAppercu();
    void afficherMessage();
    void colorierCase(int i, int j);
    void enregistrerChoixVoisinage();
};

#endif // CHOIXVOISINAGE_H
