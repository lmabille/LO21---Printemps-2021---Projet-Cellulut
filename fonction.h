//
// Created by Anne LAHNECHE on 05/05/2021.
//

#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_FONCTION_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_FONCTION_H
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
#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_FONCTION_H
