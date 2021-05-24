//
// Created by thoma on 13/05/2021.
//

#include "etat.h"


string Etat::getEtat() {
    return this->label;
}



/*void Etat::setEtat(string newEtat) {
    if(this->l_etat_possible[0] == ""){
        cout << "Liste etats pas definie ! Echec " << endl;
        return;
    }
    if(this->l_etat_possible->find(newEtat)<10){
        cout << this->getListe()[0];
        this->label = newEtat;
    }
    else {
        cout << "N'apparatient pas a la liste des etats possibles" << endl;
    }



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

string *Etat::getListe() {

    return this->l_etat_possible;
}*/



Etat::Etat() {
    //l_etat_possible[0] = "";
    label = "";
    indice=0;
}
