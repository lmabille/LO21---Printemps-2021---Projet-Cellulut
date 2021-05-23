#include <iostream>
#include "configuration.h"

/*** Classe Configuration ***/

Configuration::Configuration(Reseau *r): pavage(r)
{
    // Allocation mémoire
    auto valeurs = new Cellule** [r->abscisse];
    for (unsigned int i=0;i<r->abscisse;i++)
    {
        *(valeurs+i) = new Cellule* [r->ordonnee];
    }
    // Remplissage initial (tous les états = 0)
    for (unsigned int i=0;i<r->abscisse;i++)
    {
        for (unsigned int j=0;j<r->ordonnee;j++)
        {
            *(*(valeurs+i) +j) = new Cellule(i,j);
        }
    }
}

Configuration::getEtatCellule(int i, int j) const
{
    return grille[i][j].etat;
}
