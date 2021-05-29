//
// Created by Anne LAHNECHE on 24/05/2021.
//
#include "configuration.h"
#include "etat.h"
#include "etat_reseau.h"
#include "Modele.h"
#include "simulateur.h"
#include "voisinage.h"
#include "outils.h"
#include "chargerModele.h"

Simulateur *Simulateur::uniqueInstance = nullptr;

int main() {
    /*
    Modele * t2 = new Modele;
    //t2->typeVoisinnage = new Voisinage(10);
    cout << t2->typeVoisinnage->getNbCelluleVoisi();
    t2->typeVoisinnage->setNbCellule(5);
    cout << t2->typeVoisinnage->getNbCelluleVoisi();
    //t2->getVoisin()->setNbCellule(2);
    */

    Modele* test = chargerModel("C:\\Users\\thoma\\Documents\\UTC\\ProjetLo21\\LO21---Printemps-2021---Projet-Cellulut\\test.xml");


    cout << test->getAuteur() <<endl;
    cout << test->getDescription() <<endl;
    cout << test->getTitre() <<endl;
    cout << test->getAnnee() <<endl;
    cout << test->getEnsemble()->getNombreEtats() <<endl;
    cout << test->getEnsemble()->getListe()[1].getLabel()<<endl;
    cout << test->getEnsemble()->getListe()[1].getIndice() <<endl;


    Case* voisi = test->getVoisin()->getTableau();
    for (int i =0; i<test->getVoisin()->getNbCelluleVoisi(); i++) {
        cout << voisi[i].getL() << " " << voisi[i].getC() <<endl;
    }

    FonctionTransition* fct = test->getFonction();
    for (int i = 0 ; i< fct->getTaille(); i++) {
        cout <<fct->getTableau()[i] <<endl;
    }




    return 0;
}
