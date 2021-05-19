//
// Created by Anne LAHNECHE on 05/05/2021.
//

#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_FONCTION_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_FONCTION_H
#include <stdio.h>
#include "etat.h"
#include "configuration.h"
class Cellule {
    int x;
    int y;
    Etat * etat;
    friend configuration;
    Cellule(int x, int y) : x(x), y(y) {};
    Cellule(int x, int y, Etat * e) : x(x), y(y) , etat(e){};
    void set_etatcellule(Etat* etat);

public:

    void get_x(){ return x ;};
    void get_y(){ return y ;};
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

class Case;

class Voisinage{
    Case ** ensemble_de_case;
    size_t taille = 0 ;
public :
    Voisinage();
    Case ** Ajouter_Case(Case* c);
};

class Case{
    int x;
    int y;
    friend Voisinnage;
    Case(int X, int Y) : x(X), y(Y){};
};
#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_FONCTION_H
