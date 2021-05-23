#include <iostream>
#include "configuration.h"

/*** Etats ***/

EnsembleEtats::EnsembleEtats(unsigned int nombre): nbEtats(nombre), etatsPossibles(new Etat[nombre])
// Les indices sont distribués de la même manière à chaque fois
{
    for (unsigned int i=0; i<nombre; i++)
    {
        etatsPossibles[i].indice = i;
    }
}

void EnsembleEtats::definirEtats()
// Les couleurs et labels sont configurables par l'utilisateur
{
    for (unsigned int i=0;i<nbEtats;i++)
    {
        cout << "couleur de l'etat " << i << " :";
        cin >> etatsPossibles[i].couleur;
        cout << "label de l'etat " << i << " :";
        cin >> etatsPossibles[i].label;
    }
}

/*class Configuration
{
    Reseau* pavage;
    unsigned int rang;
    Cellule** valeurs = nullptr; // 2D

public:
    Configuration(Reseau& r);
    Configuration(const Configuration& c);
    ~Configuration();
    Configuration& operator=(const Configuration& c);
};
*/

/*** Classe Configuration ***/

Configuration::Configuration(Reseau *r): pavage(r)
{
    // Allocation mémoire
    valeurs = new Cellule** [r->abscisse];
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

// Version stockage des états int uniquement
/*
    // Allocation mémoire des valeurs
    valeurs = new int* [r->abscisse];
    for (unsigned int i=0;i<r->abscisse;i++)
    {
        *(valeurs +i) = new int [r->ordonnee];
    }
    // Remplissage à l'initialisation
    for (unsigned int i=0;i<r->abscisse;i++)
    {
        for (unsigned int j=0; j<r->ordonnee;j++)
        {
            valeurs[i][j] = 0;
        }
    }
*/
