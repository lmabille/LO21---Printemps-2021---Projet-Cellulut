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
#include <QApplication>
#include "affichage_info.h"
#include "menuprincipale_2.h"
#include "qSimulateur.h"


Simulateur *Simulateur::uniqueInstance = nullptr;

int main(int argc, char* argv[]) {
    //Laurine
  /*  std::cout<<"yo";
    QApplication app(argc, argv);
    std::cout<<"yo";
    Etat *listeEtat=new Etat[4];
    Etat e1(0, "mort", "noir");
    Etat e2(0, "vivant", "blanc");
    Etat e3(0, "vener", "rouge");
    Etat e4(0, "chill", "bleu");
    listeEtat[0]=e1;
    listeEtat[1]=e2;
    listeEtat[2]=e3;
    listeEtat[3]=e4;

    EnsembleEtats ensemble(4);
    ensemble.setListe(listeEtat);

    V_VonNeumann V;
    V.definir_ensemble_case(4);

    string * tab = new string[4];
    tab[0]="100211";
    tab[1]="100210";
    tab[2]="123011";
    tab[3]="210321";

    FonctionTransition f(tab, 4);

   Modele *M = new Modele("testLolo3", &ensemble,  &f, "extension", &V, "Je suis la description", "Newton", 2023);

   Reseau res(3,3);

    Configuration *conf = new Configuration(res, ensemble);




   // std::cout<<"yo";
    qSimulateur fenetre(nullptr, M, conf);
    std::cout<<"yo";

    fenetre.show();
    return app.exec();*/

    /*std::cout<<"Yo !";

    Etat *listeEtat=new Etat[4];
    Etat e1(0, "mort", "noir");
    Etat e2(0, "vivant", "blanc");
    Etat e3(0, "vener", "rouge");
    Etat e4(0, "chill", "bleu");
    listeEtat[0]=e1;
    listeEtat[1]=e2;
    listeEtat[2]=e3;
    listeEtat[3]=e4;*/


    //On crée l'ensemble d'état
   /* EnsembleEtats ensemble(4);
    ensemble.setListe(listeEtat);



    V_VonNeumann V;
    V.definir_ensemble_case(4);*/

    //On crée la fonction de transition
    /*string * tab = new string[4];
    tab[0]="100211";
    tab[1]="100210";
    tab[2]="123011";
    tab[3]="210321";

    FonctionTransition f(tab, 4);*/

    //On crée le modèle

  /*  Modele M("testLolo3", &ensemble,  &f, "extension", &V, "Je suis la description", "Newton", 2023);
    M.sauvegardeM();*/



    //Test configuration
 //   Reseau res(3,3);

    //On initialise la configuration
   /* Configuration conf(res, ensemble);
    conf.sauvegarderConfiguration("testLolo3", "ConfigurationInitiale");*/












    /*QApplication app(argc, argv);
    information fenetre;
    MenuPrincipale_2 mn;
    fenetre.show();
    mn.show();
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


    // vio

   // EnsembleEtats * ensembleEtats = new EnsembleEtats(2);
    /*ensembleEtats->definirEtats();
    for (int i=0; i<ensembleEtats->getNombreEtats();i++)
    {
        cout << "etat[" << ensembleEtats->getListe()[i].getIndice() << "]" << " : " << ensembleEtats->getListe()[i].getLabel() << "\n";
    }*/

  /*  ensembleEtats->getListe()[0].setIndice(0);
    ensembleEtats->getListe()[0].setlabel("A");

    ensembleEtats->getListe()[1].setIndice(1);
    ensembleEtats->getListe()[1].setlabel("B");

     Reseau res(3,3);
    Configuration* configDepart = new Configuration(res, *ensembleEtats);*/

     //test getVoisinage ;
/*    Etat* mort = (*ensembleEtats)[0];
    Etat* vivant = (*ensembleEtats)[1];
   cout << "\ntests recup mort et vivant\n";
    cout << mort->getIndice() << " " << mort->getLabel() << endl;
    cout << vivant->getIndice() << " " << vivant->getLabel() << endl;

    configDepart->setEtatCellule(1,0,vivant); // cell de gauche
    configDepart->setEtatCellule(0,1,vivant); // cell du haut // les autres sont à "mort" par initialisation
    cout << "tests setEtatCellule" << endl;
    cout << configDepart->getEtatCellule(1,0).getIndice() << " " << configDepart->getEtatCellule(1,0).getLabel() << endl;
    cout << configDepart->getEtatCellule(0,1).getIndice() << " " << configDepart->getEtatCellule(0,1).getLabel() << endl;*/
    /*Case * liste_cases = new Case[4];
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
    v->setensemble_case(liste_cases);*/

    //cout << configDepart->getVoisinage(2,2,*v)<<"\n";

  /*  V_Moore moore;
    moore.definir_ensemble_case(1);*/


    // orhane
 //   auto tab = new string[2];

    /*tab[0]="1101000000";
    tab[1]="1000100000";
    tab[2]="0001100001";
    tab[3]="0101000001";*/

  /*  tab[0]="1710";
    tab[1]="0621";

    FonctionTransition * f;
    f = new FonctionTransitionIntention(tab, 2);

    Modele m("modele 1",ensembleEtats, f, &moore, "ta race", "Orhane", 2021);

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
    }*/


// vio

/*V_VonNeumann vonneum;
vonneum.definir_ensemble_case(2);*/
return 0;
}



