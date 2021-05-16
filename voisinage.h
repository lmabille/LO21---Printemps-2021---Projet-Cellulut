//
// Created by thoma on 13/05/2021.
//

#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_VOISINAGE_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_VOISINAGE_H

using namespace  std;
#include <iostream>
#include <cstdio>


class Case;


class Voisinage {
private:

    Case ** ensemble_case;

    int nbCelluleVoisi;
    string typeVoisi;
    void setNbCellule(int nb);




public:
    Voisinage();
    const string getTypeVoisi();
    const int getNbCelluleVoisi() const;

    Case ** getTableau();


};

class Case{ // Classe case
    int x;
    int y;
    friend Voisinage;
    Case(int X, int Y) : x(X), y(Y){};

public:
    int getX();
    int gety();
    void setX(int x);
    void setY(int y);
};



#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_VOISINAGE_H
