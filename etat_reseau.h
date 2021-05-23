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
    friend class Configuration;
    Cellule(int x, int y) : x(x), y(y) {};
    Cellule(int x, int y, Etat * e) : x(x), y(y) , etat(e){};
    void set_etatcellule(Etat* etat);
    friend class Simulateur;

public:
    int get_x(){ return x ;};
    int get_y(){ return y ;};
    Etat & get_Etat(){ return *etat;};
};

class Reseau {
    int Longueur;
    int Largeur;
    friend configuration;
    Reseau()=default;
    Reseau(int lon=0, int lar=0) : Longueur(lon), Largeur(lar) {};

public:
    int get_long(){return Longueur;};
    int get_larg(){return Largeur; }
};



#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_FONCTION_H
