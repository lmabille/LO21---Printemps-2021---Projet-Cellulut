#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_MODELE_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_MODELE_H
#include<string>
#include<cstdio>
#include "voisinage.h"
#include "etat.h"

using namespace std;

class FonctionTransition{
    string * tableau;
    friend class Simulateur;

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
    /*Modele(string t, Etat **e, string r[1000], Voisinage *v, string d, string a="",unsigned int annee=0):titre(t), ensembleEtat(e), regles(r), typeVoisinnage(v), description(d), auteur(a), anneeCreation(annee){}
    ~Modele(){
        delete[] ensembleEtat;
    }
    const string& getTitre() const {return titre; }
    Etat ** const getEtat() const {return ensembleEtat;}*/
    const string& getRegles() const {return *regles; }
    const Voisinage *getVoisin() const {return typeVoisinnage; }
    const string& getDescription() const {return description; }
    const string& getAuteur() const {return auteur; }
    const string& getTitre() const {return titre; }
    void setAutheur(string nom){this->auteur = nom; }
    void setTitre(string titre) { this->titre = titre ;}
    void setDesc(string desc) {this->description = desc; }
    void setAnnee(int annee) {this->anneeCreation = annee;}
    void initEnsemble(int n) { this->etatsPossibles = new EnsembleEtats(n) ;}
    EnsembleEtats* getEnsemble() {return etatsPossibles;};
    int getAnnee() const {return anneeCreation; }
    void chargerModele(FILE *f);//charge les éléments du fichier puis fait appel au constructeur
    void creerModele();//propose choix à l'utilisateur, génère règles puis fait appel au constructeur
    FILE *sauvegarderModele();//sauvegarde l'ensemble des attributs dans un fichier xml
    void appliquerTransition();

};

#endif


