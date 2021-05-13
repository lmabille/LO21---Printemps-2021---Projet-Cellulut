//
// Created by thoma on 13/05/2021.
//

#include "voisinage.h"

int Voisinage::getNbCelluleVoisi() {
    return this->nbCelluleVoisi;
}

string Voisinage::getTypeVoisi() {
    return this->typeVoisi;
}

void Voisinage::initVoisinage() {
    if(this->typeVoisi == ""){
        cout << "Le type de voisinage n'est pas défini. Echec initialisation." << endl;
        return;
    }
    else
    {

    }
}

void Voisinage::setNbCellule(int nb) {
    if(nb >=0)
        this->nbCelluleVoisi = nb;
    else
        cout << "Nombre négatif. Erreur" << endl;


}

Voisinage::Voisinage() {
    nbCelluleVoisi = 0;
    typeVoisi  ="";
    Co_X[0] = 0;
    Co_Y[0] = 0;
}

int *Voisinage::getCoX() {
    return this->Co_X;
}

int *Voisinage::getCoY() {
    return this->Co_Y;
}
