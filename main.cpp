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

#include <stdio.h>
#include <string.h>

using namespace std;

Simulateur *Simulateur::uniqueInstance = nullptr;

int main() {

    Modele* test = chargerModel("C:\\Users\\thoma\\Documents\\UTC\\ProjetLo21\\LO21---Printemps-2021---Projet-Cellulut\\test.xml");
    cout << test->getAuteur() <<endl;
    cout << test->getDescription() <<endl;
    cout << test->getTitre() <<endl;
    cout << test->getAnnee() <<endl;
    cout << test->getEnsemble()->getNombreEtats();











    return 0;
}