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
    // string l_etat_possible[10];
    friend class Modele;

public:
    Etat();
    int getIndice(){return indice;}
    string getEtat();
    void setIndice(int i) {indice = i;}
    void setlabel(string s){ label = s;}
    //void setEtat(string newEtat);
    //void defListEtat(string newListe[10]);
    string* getListe();
    

};



#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_ETAT_H
