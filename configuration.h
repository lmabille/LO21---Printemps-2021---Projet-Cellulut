#ifndef CELLULUT_H_INCLUDED
#define CELLULUT_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;

class Reseau
// Le r�seau donnne les dimensions x et y du pavage pour la simulation
{
    unsigned int abscisse;
    unsigned int ordonnee;
    friend class Configuration;
};

class Etat
// L'�tat d'une cellule est d�sign� par un indice, une couleur et un label
{
    int indice;
    string couleur;
    string label;
    friend class EnsembleEtats;
    friend class Cellule;
};

class Cellule
{
    Etat etat;
};

class Voisinage
// Un voisinage est une sous-classe de Configuration, c'est une matrice centr�e autour d'une cellule en particulier
// NB : c'est une super-classe
{
    Cellule** voisinage = nullptr;
    string nom;

public:
    Voisinage(unsigned int i, unsigned int j);
    ~Voisinage();
};
// D�finir au moins les 3 voisinages du sujet


class Configuration
// Prend en argument un pavage qui lui donne des dimensions
// Donne � toutes les cellules un �tat
// Doit pouvoir �tre construite par recopie/ =
// Doit pouvoir �tre construite al�atoirement (config de d�part)
// Doit pouvoir �tre construite manuellement (config de d�part)
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

// Il faut une classe en charge de set la configuration avec les �tats de l'automates
class setConfiguration
{
    Automate *automate; // ou directement etatsPossibles ?
    Configuration *config;
public:
    void setConfiguration()
};

class ModeledAutomate
// fonction de transition(composition) + ensemble d'�tats(composition) + voisinage (peut �tre choisi)
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
    void fonctionTransition(Configuration* dep, Configuration* dest); // red�finie pour toutes les sous-classes
    ModeledAutomate(Voisinage v, EnsembleEtats etats, string t = "inconnu", string desc = "inconnu", string aut = "inconnu", string crea = "inconnu");
};

class Simulateur
// Applique un automates sur plusieurs g�n�rations = moteur
// Singleton
{
    // Configuration d�part
    // next() (appliquerTransition)
    // etc.
};

#endif // CELLULUT_H_INCLUDED
