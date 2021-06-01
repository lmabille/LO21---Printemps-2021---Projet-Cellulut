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
    Etat(int i, string l, string c): indice(i), label(l), couleur(c){}
    int getIndice() {return indice;}
    string getLabel();
    string getCouleur(){return couleur;}
    void setIndice(int i) {indice = i;}
    void setlabel(string s) { label = s;}
    // setCouleur void setCouleur; // à définir
    string* getListe();
};

class EnsembleEtats // désigne un ensemble donné d'états possibles // serait cool en singleton car une seule instance par simulation
{
    int nombreEtats = 0;
    Etat* liste;


public:
    EnsembleEtats(int n): nombreEtats(n), liste(new Etat[n]) {}
    void definirEtats();
    int getNombreEtats() {return this->nombreEtats;}
    void setListe(Etat* lst) { this->liste = lst;}
    void setNombreEtat(int nb) { this->nombreEtats = nb; cout  << "test" <<endl;}
    // bool checkExisteDeja(const Etat& e);
    Etat* operator[](int indice);
    Etat * getListe(){return liste;}
};

#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_ETAT_H
