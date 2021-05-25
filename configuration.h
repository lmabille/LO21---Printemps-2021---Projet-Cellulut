#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_CONFIGURATION_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_CONFIGURATION_H
#include <iostream>
#include <string>
#include "etat_reseau.h"
#include "voisinage.h"

using namespace std;

class Configuration
{
    // les cellules ont pour seul attribut leur �tat
    Reseau reseau;
    Cellule** grille = nullptr;
    friend class Simulateur;

public:
    // constructeurs & destructeurs
    Configuration()=default;
    Configuration(const Reseau &r);
    Configuration(const Reseau &r, EnsembleEtats& etatsPossibles);
    Configuration(const Configuration& c);
    // + d�finir un constructeur qui g�n�re une grille al�atoirement
    ~Configuration();
    Configuration& operator=(const Configuration& c);
    // accesseurs en �criture
    // void setGrille(Cellule **c){grille=c;}
    // void setReseau(Reseau &r){reseau=r;}
    void setEtatCellule (int i, int j, Etat* e) {grille[i][j].set_etatcellule(e);}
    // accesseurs en lecture
    Cellule& getCellule (int i, int j) const {return grille[i][j];}
    int getReseauLignes() const {return reseau.get_nbLignes();}
    int getReseauColonnes() const {return reseau.get_nbCols();}
    Etat& getEtatCellule (int i, int j) const {return grille[i][j].get_Etat();}
    string& getVoisinage (int i, int j, Voisinage& typeVois) const;
    // friend de cellule
};

#endif // CELLULUT_H_INCLUDED
