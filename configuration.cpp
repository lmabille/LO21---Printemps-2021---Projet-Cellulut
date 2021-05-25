#include <iostream>
#include "configuration.h"
#include "etat_reseau.h"

/*** Classe Configuration ***/

Configuration::Configuration(const Reseau &r): reseau(r)
/* Initialise simplement une grille de cellules avec les bonnes dimensions (se charge des allocations mémoire) */
{
    // Allocation mémoire
    auto grille = new Cellule* [r.nb_lignes];
    for (unsigned int i=0; i<r.nb_lignes; i++)
    {
        *(grille+i) = new Cellule[r.nb_colonnes];
    }
}

Configuration::Configuration(const Reseau &r, EnsembleEtats& etatsPossibles): reseau(r)
/* Initialise une grille de cellule et met par défaut toutes les cellules à l'état 0 */
{
    // Allocation mémoire
    auto grille = new Cellule* [r.nb_lignes];
    for (unsigned int i=0; i<r.nb_lignes; i++)
    {
        *(grille+i) = new Cellule[r.nb_colonnes];
    }
    // remplissage avec l'état[0] par défaut
    for (unsigned int i=0; i<r.nb_lignes; i++)
    {
        for (unsigned int j = 0; j<r.nb_colonnes; j++)
        {
            grille[i][j].set_etatcellule(etatsPossibles[0]);
            // cout << "[" << i << "," << j << "] : " << grille[i][j].get_Etat().getIndice() << " "; // fonctionne bien
            // cout << "[" << i << "," << j << "] : " << grille[i][j].get_Etat().getLabel() << "\n"; // fonctionne bien
        }
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
    for (int i = 0; i<reseau.nb_lignes; i++)
    {
        delete[] grille[i];
    }
    delete[] grille;
}

Configuration& Configuration::operator=(const Configuration& c)
{
    if (this != &c)
    {
        reseau = c.reseau;
        Cellule** newGrille = new Cellule* [reseau.nb_lignes];
        for (unsigned int i=0; i<reseau.nb_lignes; i++)
        {
            *(newGrille+i) = new Cellule[reseau.nb_colonnes];
        }
        Cellule** oldGrille = grille;
        grille = newGrille;
        delete oldGrille;
        /*for (int i = 0; i<reseau.nb_lignes; i++)
        {
            delete[] oldGrille[i];
        }*/
        //delete[] oldGrille;
        // remplissage ? nécessaire ou pas ?
        for (int i=0; i<reseau.nb_lignes; i++)
        {
            for (int j=0; j<reseau.nb_colonnes; j++)
            {
                grille[i][j] = newGrille[i][j];
            }
        }
    }
    return *this;
}
