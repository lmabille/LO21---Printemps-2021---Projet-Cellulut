#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H
#include <iostream>
#include <string>
#include "etat_reseau.h"

using namespace std;

class Configuration
{
    Cellule** grille = nullptr; // les cellules ont pour seul attribut leur état
    Reseau* reseau;
    friend class Simulateur;

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
