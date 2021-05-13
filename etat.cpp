//
// Created by thoma on 13/05/2021.
//

#include "etat.h"


string Etat::getEtat() {
    return this->label;
}



void Etat::setEtat(string newEtat) {
    this->label = newEtat;

}

void Etat::defListEtat(string *newListe) {
    for (int i =0; i<10; i++) {
        this->l_etat_possible[i] = "";
    }
    int cpt = 0;
    while (!newListe[cpt].empty()) {
        this->l_etat_possible[cpt] = newListe[cpt];
        cpt ++;

    }
}
