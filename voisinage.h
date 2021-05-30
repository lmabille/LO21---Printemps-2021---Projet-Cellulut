//
// Created by thoma on 13/05/2021.
//

#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_VOISINAGE_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_VOISINAGE_H

using namespace std;
#include <iostream>
#include <cstdio>

class Case
{ // Classe case
    int l;
    int c;
    //friend Voisinage;

public:
    int getL() const { return l; };
    int getC() const { return c; };
    void setL(int newL) { this->l = newL; }
    void setC(int newC) { this->c = newC; }
    Case() = default;
    Case(int L, int C) : l(L), c(C){};
};

class Voisinage
{
    int nbCelluleVoisi;
    string typeVoisi;
    Case *ensemble_case;
    friend class Modele;
    // friend class Simulateur;
public:
    Voisinage()=default;
    Voisinage(int n) : nbCelluleVoisi(n), ensemble_case(new Case[n]) { typeVoisi = ""; };
    const string getTypeVoisi();
    const int getNbCelluleVoisi() const;
    void setNbCellule(int nb);
    void setensemble_case(Case *c) { ensemble_case = c; };
    void setType(string t) { typeVoisi = t; }
    Case *getTableau();
    Case &operator[](int indice);
};

#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_VOISINAGE_H
