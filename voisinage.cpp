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
    nbCelluleVoisi = 10;
    typeVoisi  ="";
    ensemble_case = new Case[10]();

}

Case *Voisinage::getTableau() {
    return this->ensemble_case;
}

Case& Voisinage::operator[](int indice)
{
    try {
        if (indice < 0 || indice >= nbCelluleVoisi)
            throw string("case n'existe pas !"); // à remplacer par AutomateException comme dans le td
        else
            return ensemble_case[indice];
    }
    catch (string const& erreur)
    {
        cout << erreur << endl;
    }
}


