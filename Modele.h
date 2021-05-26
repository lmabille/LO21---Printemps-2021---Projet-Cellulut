#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_MODELE_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_MODELE_H
#include<string>
#include<cstdio>
#include "voisinage.h"
#include "etat.h"
#include "configuration.h"

using namespace std;

class FonctionTransition{
    string * tableau;
    friend class Modele;

public:
    FonctionTransition(string * tab) : tableau(tab){};
    FonctionTransition()=default;
};

class Modele{
    string titre; //key
    EnsembleEtats* etatsPossibles; // à prendre en compte dans les constructeurs/ destructeurs!
    string *regles;
    Voisinage *typeVoisinnage;
    FonctionTransition *fonctionTrans;
    string description;
    string auteur;
    unsigned int anneeCreation;
    friend class Simulateur;

public :
    Modele()=default;
    Modele(string t, EnsembleEtats *e, FonctionTransition * f, Voisinage *v, string d, string a="",unsigned int annee=0):titre(t), etatsPossibles(e), fonctionTrans(f), typeVoisinnage(v), description(d), auteur(a), anneeCreation(annee){}
    ~Modele(){delete[] etatsPossibles;} // pas sûr de ça // + voir le destructeur de la classe EnsembleEtats
    const string& getTitre() const {return titre; }
    EnsembleEtats* const getEtatsPossibles() const {return etatsPossibles;}
    const string& getRegles() const {return *regles; }
    const Voisinage *getVoisin() const {return typeVoisinnage; }
    const string& getDescription() const {return description; }
    const string& getAuteur() const {return auteur; }
    int getAnnee() const {return anneeCreation; }
    void chargerModele(FILE *f);//charge les éléments du fichier puis fait appel au constructeur
    void creerModele();//propose choix à l'utilisateur, génère règles puis fait appel au constructeur
    FILE *sauvegarderModele();//sauvegarde l'ensemble des attributs dans un fichier xml
    void appliquerTransition(const Configuration &dep, Configuration &dest) const;
};

#endif


