#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_CONFIGURATION_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_CONFIGURATION_H
#include <iostream>
#include <string>
#include "etat_reseau.h"

using namespace std;

class Configuration
{
    // les cellules ont pour seul attribut leur état
    Reseau* reseau;
    friend class Simulateur;
    Cellule** grille = nullptr;
public:
    // constructeurs & destructeurs
    Configuration();
    Configuration(const Configuration& c);
    ~Configuration();
    Configuration& operator=(const Configuration& c);
    // accesseurs cellule
    Etat& getEtatCellule(int i, int j) const;
};

#endif // CELLULUT_H_INCLUDED
