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
#include "menuprincipale_2.h"
#include "qSimulateur.h"
#include "informations.h"
#include "choix_modele.h"
#include "taille_reseau.h"
#include "config.h"
#include "fenetreconfiguration.h"
#include "chargerModele.h"
#include "ChoixVoisinage.h"
#include "creaconfig.h"


Simulateur *Simulateur::uniqueInstance = nullptr;

int main(int argc, char* argv[]) {

    // viovio
/*
    QApplication app(argc, argv);

    Case* cases = new Case[3];
    cases[0].setL_C(1,1);
    cases[1].setL_C(-1,1);
    cases[2].setL_C(1,-1);

    V_ChoixUtilisateur* vU = new V_ChoixUtilisateur;
    vU->setensemble_case(cases);

    std::cout << vU->getNbCelluleVoisi();


    return app.exec();
*/



    QApplication app(argc, argv);

    ChoixVoisinage* fenetreVois = new ChoixVoisinage(nullptr, 7, 7); // nullptr, 3, 3 par défaut

    fenetreVois->show();
    return app.exec();


  /*     QApplication app(argc, argv);

       MenuPrincipale_2 M;
       M.show();
*/
/*
        Etat *listeEtat=new Etat[2];
        Etat e1(0, "mort", "pepper mint");
        Etat e2(1, "vivant", "blanc");
        listeEtat[0]=e1;
        listeEtat[1]=e2;

        EnsembleEtats ensemble(2);
        ensemble.setListe(listeEtat);

        V_VonNeumann V;
        V.definir_ensemble_case(1);

        string * tab = new string[21]; // st+1

       // std::cout << "yo";

        tab[0] = "0111000001";
        tab[1] = "0011100001";
        tab[2] = "0001110001";
        tab[3] = "0000111001";
        tab[4] = "0000011101";
        tab[5] = "0111110001";

        tab[6] = "1000000000";
        tab[7] = "1100000000";
        tab[8] = "1010000000";
        tab[9] = "1001000000";
        tab[10] = "1000100000";
        tab[11] = "1000010000";
        tab[12] = "1000001000";
        tab[13] = "1000000100";
        tab[14] = "1000000010";
        tab[15] = "0101010001";
        tab[16] = "0001010001";
        tab[17] = "0001000011";
        tab[18] = "0001000101";
        tab[19] = "0111000101";
        tab[20] = "0110000001";

        FonctionTransition f(tab, 21);

        Modele *M = new Modele("testLolo3", &ensemble,  &f, "extension", &V, "Je suis la description", "Newton", 2023);
        M->sauvegardeM();

        Reseau res(10,10);

        Configuration *c1 = new Configuration(res, ensemble);
        Configuration *c2 = new Configuration(res, ensemble);
        Configuration *c3 = new Configuration(res, ensemble);
        Configuration *c4 = new Configuration(res, ensemble);
        Configuration *c5 = new Configuration(res, ensemble);

        c1->remplissageAleatoire(ensemble);

        qSimulateur fenetre(nullptr, M, c1);

        fenetre.show();*/

        return app.exec();



     //Thomas
  /*  QApplication app(argc, argv);
    const char * fichier = "C:\\Users\\thoma\\Documents\\UTC\\ProjetLo21\\LO21---Printemps-2021---Projet-Cellulut\\Modeles\\testLolo3.xml";

    Modele* model = chargerModel(fichier);

    Simulateur* simu = new Simulateur(*model);
    Reseau res(10,10);

    FenetreConfiguration f_config(nullptr,model,simu,fichier);
    f_config.show();

    Configuration *c1 = new Configuration(res);*/
    /*Configuration *c2 = new Configuration(res);
    Configuration *c3 = new Configuration(res);
    Configuration *c4 = new Configuration(res);
    Configuration *c5 = new Configuration(res);

    //c1->remplissageAleatoire(ensemble);

    qStdOut() <<"indice de 0 :" <<QString::number(model->getEnsemble()->getListe()[0].getIndice());

    qStdOut() <<"indice de 1 :" <<QString::number(model->getEnsemble()->getListe()[1].getIndice());

*/


  //  return app.exec();
   // delete c1;


}


    //Lucas
  /*  QApplication app(argc, argv);

    config fenetre_config;
    fenetre_config.show();
    return app.exec();


}*/






    //Laurine
/*   std::cout<<"yo";
    QApplication app(argc, argv);
     Etat *listeEtat=new Etat[2];
    Etat e1(0, "mort", "noir");
    Etat e2(1, "vivant", "blanc");
    listeEtat[0]=e1;
    listeEtat[1]=e2;

    EnsembleEtats ensemble(2);
    ensemble.setListe(listeEtat);

    V_VonNeumann V;
    V.definir_ensemble_case(1);



      auto tab = new string[2];


       tab[0]="0401";
       tab[1]="1040";

       FonctionTransition * f;
       f = new FonctionTransitionIntention(tab, 2);

       Modele m("modele 1", &ensemble, f, "intention", &V, "ta race", "Orhane", 2021);
       m.sauvegardeM();*/
// Modele *M = new Modele("testLolo3", &ensemble,  &f, "extension", &V, "Je suis la description", "Newton", 2023);
      // auto configArrivee= new Configuration;
      /* Reseau res(4,3);

        Configuration *conf = new Configuration(res, ensemble);




        std::cout<<"yo ";
        qSimulateur fenetre(nullptr, &m, conf);
        std::cout<<"yo";
        fenetre.show();
        return app.exec();*/


    //   m.appliquerTransition(*configDepart, *configArrivee);





















  /*  std::cout<<"yo";
    Etat *listeEtat=new Etat[2];
    Etat e1(0, "mort", "noir");
    Etat e2(1, "vivant", "blanc");
    listeEtat[0]=e1;
    listeEtat[1]=e2;

    EnsembleEtats ensemble(2);
    ensemble.setListe(listeEtat);

    V_VonNeumann V;
    V.definir_ensemble_case(1);

    string * tab = new string[2];
    tab[0]="000001";
    tab[1]="111110";


    FonctionTransition f(tab, 2);

   Modele *M = new Modele("testLolo3", &ensemble,  &f, "extension", &V, "Je suis la description", "Newton", 2023);

   Reseau res(4,3);

    Configuration *conf = new Configuration(res, ensemble);




    std::cout<<"yo ";
    qSimulateur fenetre(nullptr, M, conf);
    std::cout<<"yo";
    fenetre.show();
     return app.exec();*/
  /*  MenuPrincipale_2 m;
    m.show();

    fenetre.show();
    return app.exec();

    std::cout<<"Yo !";

    Etat *listeEtat=new Etat[4];
    Etat e1(0, "mort", "noir");
    Etat e2(0, "vivant", "blanc");
    Etat e3(0, "vener", "rouge");
    Etat e4(0, "chill", "bleu");
    listeEtat[0]=e1;
    listeEtat[1]=e2;
    listeEtat[2]=e3;
    listeEtat[3]=e4;


    //On crée l'ensemble d'état
    EnsembleEtats ensemble(4);
    ensemble.setListe(listeEtat);



    V_VonNeumann V;
    V.definir_ensemble_case(4);

    //On crée la fonction de transition
    string * tab = new string[4];
    tab[0]="100211";
    tab[1]="100210";
    tab[2]="123011";
    tab[3]="210321";

    FonctionTransition f(tab, 4);*/

    //On crée le modèle

   // Modele M("testLolo4", &ensemble,  &f, "extension", &V, "Je suis la description", "Newton", 2023);
    //M.sauvegardeM();



    //Test configuration
//   Reseau res(3,3);

    //On initialise la configuration
//   Configuration conf(res, ensemble);
  //  conf.sauvegarderConfiguration("testLolo3", "ConfigurationInitiale");











/*
    QApplication app(argc, argv);
    information fenetre;
    MenuPrincipale_2 mn;
    fenetre.show();
    mn.show();
    return app.exec();
   }




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

    s.appliquerTransition(*C);*/



    // vio

   // EnsembleEtats * ensembleEtats = new EnsembleEtats(2);
/*    ensembleEtats->definirEtats();
    for (int i=0; i<ensembleEtats->getNombreEtats();i++)
    {
        cout << "etat[" << ensembleEtats->getListe()[i].getIndice() << "]" << " : " << ensembleEtats->getListe()[i].getLabel() << "\n";
    }

    ensembleEtats->getListe()[0].setIndice(0);
    ensembleEtats->getListe()[0].setlabel("A");

    ensembleEtats->getListe()[1].setIndice(1);
    ensembleEtats->getListe()[1].setlabel("B");

     Reseau res(3,3);
    Configuration* configDepart = new Configuration(res, *ensembleEtats);

     //test getVoisinage ;
    Etat* mort = (*ensembleEtats)[0];
    Etat* vivant = (*ensembleEtats)[1];
   cout << "\ntests recup mort et vivant\n";
    cout << mort->getIndice() << " " << mort->getLabel() << endl;
    cout << vivant->getIndice() << " " << vivant->getLabel() << endl;

    configDepart->setEtatCellule(1,0,vivant); // cell de gauche
    configDepart->setEtatCellule(0,1,vivant); // cell du haut // les autres sont à "mort" par initialisation
    cout << "tests setEtatCellule" << endl;
    cout << configDepart->getEtatCellule(1,0).getIndice() << " " << configDepart->getEtatCellule(1,0).getLabel() << endl;
    cout << configDepart->getEtatCellule(0,1).getIndice() << " " << configDepart->getEtatCellule(0,1).getLabel() << endl;
    Case * liste_cases = new Case[4];
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

    Voisinage* v = new Voisinage;
    v->setNbCellule(4);
    v->setensemble_case(liste_cases);

    //cout << configDepart->getVoisinage(2,2,*v)<<"\n";

    V_Moore moore;
    moore.definir_ensemble_case(1);
*/

    // orhane
 //   auto tab = new string[2];

/*    tab[0]="1101000000";
    tab[1]="1000100000";
    tab[2]="0001100001";
    tab[3]="0101000001";

    tab[0]="1710";
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

//V_VonNeumann vonneum;
//vonneum.definir_ensemble_case(2);
//return 0;
//}





