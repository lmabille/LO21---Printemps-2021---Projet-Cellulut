#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H
#include <iostream>
#include <string>
#include "etat_reseau.h"

using namespace std;



// Définir au moins les 3 voisinages du sujet


class Configuration
// Prend en argument un pavage qui lui donne des dimensions
// Donne à toutes les cellules un état
// Doit pouvoir être construite par recopie/ =
// Doit pouvoir être construite aléatoirement (config de départ)
// Doit pouvoir être construite manuellement (config de départ)
// NB : tore
{
    Reseau* pavage;
    Cellule** grille = nullptr;

public:
    Configuration(Reseau* r);
    Configuration(const Configuration& c);
    ~Configuration();
    Configuration& operator=(const Configuration& c);
    void setCellule(int i, int j, Etat* e);
    Etat getCellule(int i, int j) const;
};

// Il faut une classe en charge de set la configuration avec les états de l'automates
class setConfiguration
{
    Automate *automate; // ou directement etatsPossibles ?
    Configuration *config;
public:
    void setConfiguration()
};

class ModeledAutomate
// fonction de transition(composition) + ensemble d'états(composition) + voisinage (peut être choisi)
// NB : super-classe
{
    std::string titre;
    std::string description;
    std::string auteur;
    std::string anneeCreation;

    Etat* etatsPossibles = nullptr;
    Voisinage voisinage;

public:
    void definirEtats();
    void fonctionTransition(Configuration* dep, Configuration* dest); // redéfinie pour toutes les sous-classes
    ModeledAutomate(Voisinage v, EnsembleEtats etats, string t = "inconnu", string desc = "inconnu", string aut = "inconnu", string crea = "inconnu");
};

class Simulateur
// Applique un automates sur plusieurs générations = moteur
// Singleton
{
    // Configuration départ
    // next() (appliquerTransition)
    // etc.
};

#endif // CELLULUT_H_INCLUDED
