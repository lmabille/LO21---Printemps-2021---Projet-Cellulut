//
// Created by Anne LAHNECHE on 05/05/2021.
//

#include "etat_reseau.h"

void Cellule::set_etatcellule(Etat * e){
    etat=e;
}

Reseau& Reseau::operator=(const Reseau& c)
{
    nb_lignes = c.nb_lignes;
    nb_colonnes = c.nb_colonnes;
    return *this;
}
