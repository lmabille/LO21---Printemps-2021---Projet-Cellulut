//
// Created by Anne LAHNECHE on 05/05/2021.
//

#include "etat_reseau.h"

void Cellule::set_etatcellule(Etat * e){
    etat=e;
}

Case ** Voisinage::Ajouter_Case(Case* c){
    Case** nouv = new Case*[taille+1];
    for (int i=0; i<taille; i++) nouv[i]=ensemble_de_case[i];
    nouv[taille] = c;
    taille++;
    Case** old = ensemble_de_case;
    ensemble_de_case=nouv;
    delete[] old;
};