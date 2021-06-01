//
// Created by Anne LAHNECHE on 24/05/2021.
//
//#include "configuration.h"
//#include "etat.h"
//#include "etat_reseau.h"
//#include "Modele.h"
//#include "simulateur.h"
//#include "voisinage.h"
//#include "outils.h"
#include <QApplication>
#include "affichage_info.h"

//Simulateur *Simulateur::uniqueInstance = nullptr;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    information fenetre;
    fenetre.show();
    return app.exec();
   }



    /*
    Reseau r(3, 3);

    Etat *mort = new Etat;
    mort->setIndice(1);
    Etat *vivant = new Etat;
    vivant->setIndice(2);

    Etat ** ensemble = new Etat*[2];
    ensemble[0]=mort;
    ensemble[1]=vivant;

    string s1 = "111212";
    string s2 = "212121";

    auto regles = new string[2];
    regles[0]=s1;
    regles[1]=s2;

    Cellule c1(1,1, mort);
    Cellule c2(1,2, vivant);
    Cellule c3(1,3, mort);
    Cellule c4(2,1, vivant);
    Cellule c5(2,2, vivant);
    Cellule c6(2,3, vivant);
    Cellule c7(3,1, mort);
    Cellule c8(3,2, vivant);
    Cellule c9(3,3, vivant);

    Case ca1(0,1);
    Case ca2(1,0);
    Case ca3(0,-1);
    Case ca4(-1,0);

    auto Ca = new Case[4];
    Ca[0]=ca1;
    Ca[1]=ca2;
    Ca[2]=ca3;
    Ca[3]=ca4;

    auto v = new Voisinage;
    v->setensemble_case(Ca);
    v->setNbCellule(4);

    Modele m("vieetmort", ensemble, regles, v, "tmax", "en y", 1992);

    Simulateur s(m);

    Configuration * C = new Configuration;

    C->setReseau(r);

    auto **grille = new Cellule*[3];
    grille[0]=new Cellule[3];
    grille[1]=new Cellule[3];
    grille[2]=new Cellule[3];

    grille[0][0]=c1;
    grille[1][0]=c2;
    grille[2][0]=c3;
    grille[0][1]=c4;
    grille[1][1]=c5;
    grille[2][1]=c6;
    grille[0][2]=c7;
    grille[1][2]=c8;
    grille[2][2]=c9;

    C->setGrille(grille);

    s.appliquerTransition(*C);
     */


    /* vio

    /* EnsembleEtats * ensembleEtats = new EnsembleEtats(2);
    ensembleEtats->definirEtats();
    for (int i=0; i<ensembleEtats->getNombreEtats();i++)
    {
        cout << "etat[" << ensembleEtats->getListe()[i].getIndice() << "]" << " : " << ensembleEtats->getListe()[i].getLabel() << "\n";
    }

     Reseau res(3,3);
    Configuration* configDepart = new Configuration(res, *ensembleEtats);

     test getVoisinage
    Etat* mort = (*ensembleEtats)[1];
    Etat* vivant = (*ensembleEtats)[2];
   cout << "\ntests recup mort et vivant\n";
    cout << mort->getIndice() << " " << mort->getLabel() << endl;
    cout << vivant->getIndice() << " " << vivant->getLabel() << endl;
/*
    configDepart->setEtatCellule(1,0,vivant); // cell de gauche
    configDepart->setEtatCellule(0,1,vivant); // cell du haut // les autres sont à "mort" par initialisation
    cout << "tests setEtatCellule" << endl;
    cout << configDepart->getEtatCellule(1,0).getIndice() << " " << configDepart->getEtatCellule(1,0).getLabel() << endl;
    cout << configDepart->getEtatCellule(0,1).getIndice() << " " << configDepart->getEtatCellule(0,1).getLabel() << endl;*
/*
    Case* liste_cases = new Case[4];
    Case gauche(0,-1);
    Case haute(-1,0);
    Case droite(0,1);
    Case bas(1,0);
    liste_cases[0] = gauche;
    liste_cases[1] = haute;
    liste_cases[2] = droite;
    liste_cases[3] = bas;
    cout << "tests set up liste cases" << endl;
    cout << "[" << gauche.getL() << "," << gauche.getC() << "]" << endl;
/*
    Voisinage* v = new Voisinage;
    v->setNbCellule(4);
    v->setensemble_case(liste_cases);

    //cout << configDepart->getVoisinage(2,2,*v)<<"\n";

V_Moore moore;
moore.definir_ensemble_case(2);


    // orhane
    auto tab = new string[4];

    tab[0]="221211";
    tab[1]="211121";
    tab[2]="111222";
    tab[3]="121122";

    FonctionTransition * f = new FonctionTransition(tab, 4);

    Modele m("modele 1",ensembleEtats, f, v, "ta race", "Orhane", 2021);

    auto configArrivee= new Configuration;

    for (int i=0; i<configDepart->getReseauLignes();i++)
    {
        for (int j=0; j<configDepart->getReseauColonnes(); j++){
            cout<<configDepart->getEtatCellule(i,j).getIndice();
        }
        cout<<"\n";
    }

    m.appliquerTransition(*configDepart, *configArrivee);

    cout<<"\n";

    for (int i=0; i<configArrivee->getReseauLignes();i++)
    {
        for (int j=0; j<configArrivee->getReseauColonnes(); j++){
            cout<<configArrivee->getEtatCellule(i,j).getIndice();
        }
        cout<<"\n";
    }

 */

// vio
/*
V_VonNeumann vonneum;
vonneum.definir_ensemble_case(2);
*/

*/

