//
// Created by thoma on 13/05/2021.
//

#include "voisinage.h"

const int Voisinage::getNbCelluleVoisi() const {
    return this->nbCelluleVoisi;
}

const string Voisinage::getTypeVoisi() {
    return this->typeVoisi;
}

void Voisinage::setNbCellule(int nb) {
    if(nb >=0)
        this->nbCelluleVoisi = nb;
    else
        cout << "Nombre négatif. Erreur" << endl;
}

Voisinage::Voisinage() {
    this->nbCelluleVoisi = 10;
    this->typeVoisi  ="";
    this->ensemble_case = new Case[10]();

}

Case *Voisinage::getTableau() {
    return this->ensemble_case;
}

void Voisinage::setensemble_case(Case *c) {
    for (int i = 0 ; i < 10 ; i++) {
        this->ensemble_case[i] = c[i];
    }



    //this->ensemble_case=c;
}


int Case::getX() {
    return this->x;
}

int Case::gety() {
    return this->y;
}

void Case::setX(int newx) {
    //printf("test");
    this->x = newx;
}

void Case::setY(int y) {
    this->y = y;
}
