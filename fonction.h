//
// Created by Anne LAHNECHE on 05/05/2021.
//

#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_FONCTION_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_FONCTION_H
class cellule {
    int x;
    int y;
    Etat * etat;
    friend configuration;
    Cellule(int x, int y) : x(x), y(y) {};
    void set_etatcellule(Etat* etat);

public:

    void get_x();
    void get_y();
    Etat & get_Etat();

};
#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_FONCTION_H
