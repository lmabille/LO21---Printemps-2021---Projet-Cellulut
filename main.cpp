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

#include <stdio.h>
#include <string.h>

using namespace std;

Simulateur *Simulateur::uniqueInstance = nullptr;

int main() {

    // vio

    EnsembleEtats * ensembleEtats = new EnsembleEtats(2);
    ensembleEtats->definirEtats();
    for (int i=0; i<ensembleEtats->getNombreEtats();i++)
    {
        cout << "etat[" << (*ensembleEtats)[i]->getIndice() << "]" << " : " << (*ensembleEtats)[i]->getLabel() << "\n";
    }

    Reseau res(3,3);
    Configuration* configDepart = new Configuration(res, *ensembleEtats);

    // test getVoisinage
    Etat* mort = (*ensembleEtats)[0];
    Etat* vivant = (*ensembleEtats)[1];
/*    cout << "\ntests recup mort et vivant\n";
    cout << mort->getIndice() << " " << mort->getLabel() << endl;
    cout << vivant->getIndice() << " " << vivant->getLabel() << endl;*/// ok

    configDepart->setEtatCellule(1,0,vivant); // cell de gauche
    configDepart->setEtatCellule(0,1,vivant); // cell du haut // les autres sont à "mort" par initialisation
/*    cout << "tests setEtatCellule" << endl;
    cout << configDepart->getEtatCellule(1,0).getIndice() << " " << configDepart->getEtatCellule(1,0).getLabel() << endl;
    cout << configDepart->getEtatCellule(0,1).getIndice() << " " << configDepart->getEtatCellule(0,1).getLabel() << endl;*/// ok

    Case* liste_cases = new Case[4];
    Case gauche(0,-1);
    Case haute(-1,0);
    Case droite(0,1);
    Case bas(1,0);
    liste_cases[0] = gauche;
    liste_cases[1] = haute;
    liste_cases[2] = droite;
    liste_cases[3] = bas;
/*    cout << "tests set up liste cases" << endl;
    cout << "[" << gauche.getL() << "," << gauche.getC() << "]" << endl;*/ // ok

    Voisinage* v = new Voisinage;
    v->setNbCellule(4);
    v->setensemble_case(liste_cases);

    cout << configDepart->getVoisinage(1,1,*v)<<"\n";

    auto tab = new string[2];

    tab[0]="101012";
    tab[1]="211001";

    FonctionTransition * f = new FonctionTransition(tab);

    Modele m("modele 1",ensembleEtats, f, v, "ta race", "Orhane", 2021);

    auto configArrivee= new Configuration;


    m.appliquerTransition(*configDepart, *configArrivee);



    /*tests conversion int to char
    int i = 0;
    string* test = new string;
    *test="";
    string* a = new string;
    strcpy(a,i);
    strncat(test,a,1); */ // no need sprintf pour de simples char


    return 0;
}