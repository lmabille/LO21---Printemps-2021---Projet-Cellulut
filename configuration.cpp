#include <iostream>
#include "configuration.h"
#include "etat_reseau.h"

#include <stdio.h>
#include <string.h>

using namespace std;

/*** Classe Configuration ***/

string Configuration::getVoisinage(int i, int j, Voisinage& typeVoisi) const // à tester
{
    /* pour chaque élément du tableau ensemble de cases,
       récupère le déplacement relatif en ligne et en colonne en fonction du voisinage passé en argument,
       puis récupère l'état de la cellule i+ligneRel, j+colRel, stocke cet état
       dans un tableau de caractères, retourne ce tableau */

    string voisinage;
    int ligneRel,colRel;
    int indice;
    for (int c = 0; c < typeVoisi.getNbCelluleVoisi(); c++)
    {
        ligneRel = typeVoisi[c].getL();
        colRel = typeVoisi[c].getC();
        indice = getEtatCellule(((i+ligneRel)%reseau.nb_lignes),((j+colRel)%reseau.nb_colonnes)).getIndice();
        voisinage += to_string(indice);
        // cout << "test OK" << endl;
    }
    return voisinage;
}

Configuration::Configuration(const Reseau &r): reseau(r)
/* Initialise simplement une grille de cellules avec les bonnes dimensions (se charge des allocations mémoire) */
{
    // Allocation mémoire
    grille = new Cellule* [r.nb_lignes];
    for (unsigned int i=0; i<r.nb_lignes; i++)
    {
        *(grille+i) = new Cellule[r.nb_colonnes];
    }
}

Configuration::Configuration(const Reseau &r, EnsembleEtats& etatsPossibles): reseau(r)
/* Initialise une grille de cellule et met par défaut toutes les cellules à l'état 0 du tableau d'états possible */
{
    // Allocation mémoire
    grille = new Cellule* [r.nb_lignes];
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
        }
    }
}


Configuration::Configuration(const Configuration& c): reseau(c.reseau)
{
    // reseau = c.reseau;
    grille = new Cellule* [reseau.nb_lignes];
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
