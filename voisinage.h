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
    int nbCelluleVoisi;
    string typeVoisi;
    Case*  ensemble_case;

public:
    Voisinage();
    const string getTypeVoisi();
    const int getNbCelluleVoisi() const;
    void setNbCellule(int nb);
    Case * getTableau();

};

class Case{ // Classe case
    int x;
    int y;
    //friend Voisinage;

public:
    int getX();
    int gety();
    void setX(int newx);
    void setY(int y);
    Case() = default;
    Case(int X, int Y) : x(X), y(Y){};
};




#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_VOISINAGE_H
