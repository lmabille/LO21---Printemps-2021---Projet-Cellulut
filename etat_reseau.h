//
// Created by Anne LAHNECHE on 05/05/2021.
//

#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_ETAT_RESEAU_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_ETAT_RESEAU_H
#include <stdio.h>
#include "etat.h"

class Cellule {
    int x;
    int y;
    Etat * etat;
    Cellule(int x, int y) : x(x), y(y) {};
    void set_etatcellule(Etat* etat);
    friend class Configuration;
    friend class Simulateur;

public:
    int get_x(){ return x ;};
    int get_y(){ return y ;};
    Etat & get_Etat(){ return *etat;};
    Cellule(int x, int y, Etat * e) : x(x), y(y) , etat(e){};//le remettre en private
    Cellule() = default; // les états sont mis à 0 par défaut //remettre en private
};

class Reseau {
    int nb_lignes=0;
    int nb_colonnes=0;
    friend class Configuration;

public:
    int get_nbLignes() const {return nb_lignes;};
    int get_nbCols() const {return nb_colonnes; } ;
    Reseau& operator=(const Reseau& c);
    Reseau(int l, int c) : nb_lignes(l), nb_colonnes(c) {};//le remettre en private
    Reseau() = default;//le remettre en private
};



#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_FONCTION_H
