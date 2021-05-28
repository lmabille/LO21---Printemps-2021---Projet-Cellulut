//
// Created by thoma on 13/05/2021.
//
#include "etat.h"
#include <string.h>

Etat::Etat()
{
    label = "";
    indice=0;
}

string Etat::getLabel()
{
    return this->label;
}

void EnsembleEtats::definirEtats()
{
    int num;
    string lab;
    // + couleur
    for (int i=0; i<nombreEtats; i++)
    {
        cout << "Definition de l'etat " << i << " :\n";
        cout << "\tNumero: ";
        cin >> num; // check que ce soit bien un integer
        cout << "\tLabel: ";
        cin >> lab;
        // + couleur
        liste[i].setIndice(num);
        liste[i].setlabel(lab);
    }
}

/*
bool EnsembleEtats::checkExisteDeja(const Etat& e)
{
    for (int i = 0; i<nombreEtats; i++) {
        if (etatsPossibles[i].indice == e.indice) {
            if (etatsPossibles[i].label.compare(e.label) == 0) {
                // if couleur == couleur // définir les couleurs !! à faire
                return true;
            }
        }
    }
    return false;
}
*/

Etat* EnsembleEtats::operator[](int index)
/* Permet de retourner un pointeur sur un état alors qu'ils sont stockés dans un tableau 1D */
{
    for (int i = 0; i<nombreEtats; i++)
    {
        if (liste[i].indice==index) return &liste[i];
    }
    cout << "etat n'existe pas\n";
    return nullptr;
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




