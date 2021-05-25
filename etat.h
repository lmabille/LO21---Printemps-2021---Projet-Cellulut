//
// Created by thoma on 13/05/2021.
//

#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_ETAT_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_ETAT_H

#include <iostream>
#include <cstdio>

using namespace std;

class Etat {
private:
    int indice;
    string label;
    string couleur;
    friend class EnsembleEtats;
    friend class Modele;

public:
    Etat();
    int getIndice() {return indice;}
    string getLabel();
    void setIndice(int i) {indice = i;}
    void setlabel(string s) { label = s;}
    // setCouleur void setCouleur; // à définir
    string* getListe();
};

class EnsembleEtats // désigne un ensemble donné d'états possibles // serait cool en singleton car une seule instance par simulation
{
    Etat* liste;
    int nombreEtats = 0;

public:
    EnsembleEtats(int n): nombreEtats(n), liste(new Etat[n]) {}
    void definirEtats();
    int getNombreEtats() {return nombreEtats;}
    // bool checkExisteDeja(const Etat& e);
    Etat* operator[](int indice);
};

#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_ETAT_H
