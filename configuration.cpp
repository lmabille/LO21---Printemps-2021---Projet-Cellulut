#include <iostream>
#include "configuration.h"
#include "etat_reseau.h"

/*** Classe Configuration ***/

Configuration::Configuration(const Reseau &r): reseau(r)
{
    // Allocation mémoire
    auto grille = new Cellule* [r.nb_lignes];
    for (unsigned int i=0; i<r.nb_lignes; i++)
    {
        *(grille+i) = new Cellule[r.nb_colonnes];
    }
}

Configuration::Configuration(const Configuration& c): reseau(c.reseau)
{
    // reseau = c.reseau;
    auto grille = new Cellule* [reseau.nb_lignes];
    for (unsigned int i=0; i<reseau.nb_lignes; i++)
    {
        *(grille+i) = new Cellule[reseau.nb_colonnes];
    }
}

Configuration::~Configuration()
{
    for
    delete[] grille;
}
