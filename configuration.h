#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_CONFIGURATION_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_CONFIGURATION_H
#include <iostream>
#include <string>
#include "etat_reseau.h"

using namespace std;

class Configuration
{
    // les cellules ont pour seul attribut leur état
    Reseau reseau;
    Cellule** grille = nullptr;
    friend class Simulateur;

public:
    // constructeurs & destructeurs
    Configuration()=default;
    Configuration(const Reseau &r);
    Configuration(const Configuration& c);
    ~Configuration();
    Configuration& operator=(const Configuration& c);
    void setGrille(Cellule **c){grille=c;}
    // friend de cellule
};

#endif // CELLULUT_H_INCLUDED
