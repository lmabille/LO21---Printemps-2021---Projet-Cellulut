//
// Created by Anne LAHNECHE on 24/05/2021.
//
#include "configuration.h"
#include "etat.h"
#include "etat_reseau.h"
#include "Modele.h"
#include "simulateur.h"
#include "voisinage.h"

Simulateur *Simulateur::uniqueInstance = nullptr;

int main() {

    Reseau r(3, 3);

    Etat *mort = new Etat;
    mort->setIndice(1);
    Etat *vivant = new Etat;
    vivant->setIndice(2);

    Etat ** ensemble = new Etat*[2];
    ensemble[0]=mort;
    ensemble[1]=vivant;

    string s1 = "111212";
    string s2 = "212121";

    auto regles = new string[1000];
    regles[0]=s1;
    regles[1]=s2;

    Cellule c1(1,1, mort);
    Cellule c2(1,2, vivant);
    Cellule c3(1,3, mort);
    Cellule c4(2,1, vivant);
    Cellule c5(2,2, vivant);
    Cellule c6(2,3, vivant);
    Cellule c7(3,1, mort);
    Cellule c8(3,2, vivant);
    Cellule c9(3,3, vivant);

    Case ca1(0,1);
    Case ca2(1,0);
    Case ca3(0,-1);
    Case ca4(-1,0);

    auto Ca = new Case[4];
    Ca[0]=ca1;
    Ca[1]=ca2;
    Ca[2]=ca3;
    Ca[3]=ca4;

    auto v = new Voisinage;
    v->setensemble_case(Ca);
    v->setNbCellule(4);

    Modele m("vieetmort", ensemble, regles, v, "tmax", "en y", 1992);

    Simulateur s(m);

    Configuration C(r);

    Cellule **grille = new Cellule*[3];

    grille[0][0]=c1;
    grille[1][0]=c2;
    grille[2][0]=c3;
    grille[0][1]=c4;
    grille[1][1]=c5;
    grille[2][1]=c6;
    grille[0][2]=c7;
    grille[1][2]=c8;
    grille[2][2]=c9;

    C.setGrille(grille);

    s.appliquerTransition()

}