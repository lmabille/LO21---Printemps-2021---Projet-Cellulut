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
    int ligne=0, colonne=0;
    for (int c = 0; c < typeVoisi.getNbCelluleVoisi(); c++)
    {
        ligneRel = typeVoisi[c].getL();
        colRel = typeVoisi[c].getC();
        //calcule des coordonnées en prenant en compte que le modulo peut renvoyer des nombres négatifs
        if ((i+ligneRel)%reseau.nb_lignes<0) ligne = (i+ligneRel)%reseau.nb_lignes + reseau.nb_lignes;
        else ligne = (i+ligneRel)%reseau.nb_lignes;
        if ((j+colRel)%reseau.nb_colonnes<0) colonne = (j+colRel)%reseau.nb_colonnes + reseau.nb_colonnes;
        else colonne = (j+colRel)%reseau.nb_colonnes;
        //cout << "coordonnees du voisin " << c << " : " << endl;
        //cout << "\tligne : " << ligne << "\n" << "\tcolonne : " << colonne << endl;
        indice = getEtatCellule(ligne,colonne).getIndice();
        voisinage += to_string(indice);
        //cout << "test OK" << endl;
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
            grille[i][j].set_etatcellule(&(etatsPossibles.getListe()[0])); //modification de l'overload "[]" pour utiliser l'indice
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
