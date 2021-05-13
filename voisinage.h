//
// Created by thoma on 13/05/2021.
//

#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_VOISINAGE_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_VOISINAGE_H

using namespace  std;
#include <iostream>
#include <cstdio>





class Voisinage {
private:
    int nbCelluleVoisi;
    string typeVoisi;
    void setNbCellule(int nb);
    int Co_X[100];
    int Co_Y[100];



public:
    Voisinage();
    const string getTypeVoisi();
    const int getNbCelluleVoisi();
    void initVoisinage();
    const int* getCoX();
    const int* getCoY();


};




#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_VOISINAGE_H
