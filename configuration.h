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
    Configuration(const Reseau &r, EnsembleEtats& etatsPossibles);
    Configuration(const Configuration& c);
    // + définir un constructeur qui génère une grille aléatoirement
    ~Configuration();
    Configuration& operator=(const Configuration& c);
    // accesseurs en écriture
    void setGrille(Cellule **c){grille=c;}
    void setReseau(Reseau &r){reseau=r;}
    // accesseurs en lecture
    Cellule& getCellule(int i, int j) {return grille[i][j];}
    int getReseauLignes() {return reseau.get_nbLignes();}
    int getReseauColonnes() {return reseau.get_nbCols();}
    Etat& getEtatCellule(int i, int j) {return grille[i][j].get_Etat();}
    // friend de cellule
};

#endif // CELLULUT_H_INCLUDED
