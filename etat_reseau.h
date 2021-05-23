//
// Created by Anne LAHNECHE on 05/05/2021.
//

#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_ETAT_RESEAU_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_ETAT_RESEAU_H
#include <stdio.h>
#include "etat.h"
#include "configuration.h"
#include "simulateur.h"

class Cellule {
    int x;
    int y;
    Etat * etat;
    Cellule() {etat->indice = 0;} // les états sont mis à 0 par défaut
    Cellule(int x, int y) : x(x), y(y) {};
    Cellule(int x, int y, Etat * e) : x(x), y(y) , etat(e){};
    void set_etatcellule(Etat* etat);
    friend class Configuration;
    friend class Simulateur;

public:
    int get_x(){ return x ;};
    int get_y(){ return y ;};
    Etat & get_Etat(){ return *etat;};
};

class Reseau {
    int nb_lignes;
    int nb_colonnes;
    Reseau() = default;
    Reseau(int l=0, int c=0) : nb_lignes(l), nb_colonnes(c) {};
    friend class Configuration;

public:
    int get_nbLignes(){return nb_lignes;}
    int get_nbCols(){return nb_colonnes; }
    Reseau& operator=(const Reseau& c);
};



#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_FONCTION_H
