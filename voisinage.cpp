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
    nbCelluleVoisi = 0;
    typeVoisi  ="";
    ensemble_case = nullptr;

}

Case **Voisinage::getTableau() {
    return this->ensemble_case;
}


