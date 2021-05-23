//
// Created by Anne LAHNECHE on 24/05/2021.
//
#include "configuration.h"
#include "etat.h"
#include "etat_reseau.h"
#include "Modele.h"
#include "simulateur.h"
#include "voisinage.h"

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

    Modele m("vieetmort", reinterpret_cast<stat **>(ensemble), regles, v, "tmax", "en y", 1992);

}