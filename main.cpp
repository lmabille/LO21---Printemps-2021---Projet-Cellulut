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

Simulateur *Simulateur::uniqueInstance = nullptr;

int main() {

    // vio

    EnsembleEtats ensembleEtats(2);
    ensembleEtats.definirEtats();
    for (int i=0; i<ensembleEtats.getNombreEtats();i++)
    {
        cout << "etat[" << ensembleEtats[i]->getIndice() << "]" << " : " << ensembleEtats[i]->getLabel() << "\n";
    }

    Reseau res(3,3);
    Configuration* configDepart = new Configuration(res, ensembleEtats);

    // test getVoisinage
    Etat* mort = ensembleEtats[0];
    Etat* vivant = ensembleEtats[1];

    configDepart->setEtatCellule(-1,0,vivant);
    configDepart->setEtatCellule(0,1,vivant); // les autres sont à "mort" par initialisation

    Case* liste_cases = new Case[2];
    Case gauche(-1,0);
    Case haute(0,1);
    Case droite(1,0);
    Case bas(0,-1);
    liste_cases[0] = gauche;
    liste_cases[1] = haute;
    liste_cases[2] = droite;
    liste_cases[3] = bas;

    Voisinage* v = new Voisinage;
    v->setNbCellule(2);
    v->setensemble_case(liste_cases);
    string testVois = configDepart->getVoisinage(0,0,*v);
    cout << testVois[0]; // segmentation fault pour l'instant j'ai cours oups c'était mon premier test

    return 0;
}