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
    unsigned int taille;
    friend class Modele;

public:
    FonctionTransition(string * tab) : tableau(tab), taille(0){};
    FonctionTransition(string * tab, unsigned int t) : tableau(tab), taille(t){};
    FonctionTransition()=default;
    string *getTableau(){return tableau;}
};

class Modele{
    string titre; //key
    EnsembleEtats* etatsPossibles; // � prendre en compte dans les constructeurs/ destructeurs!
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
    ~Modele(){delete[] etatsPossibles;} // pas s�r de �a // + voir le destructeur de la classe EnsembleEtats
    const string& getTitre() const {return titre; }
    EnsembleEtats* const getEtatsPossibles() const {return etatsPossibles;}
    const string& getRegles() const {return *regles; }
    const Voisinage *getVoisin() const {return typeVoisinnage; }
    const string& getDescription() const {return description; }
    const string& getAuteur() const {return auteur; }
    FonctionTransition *getFonction(){return fonctionTrans;}
    void setAutheur(string nom){this->auteur = nom; }
    void setTitre(string titre) { this->titre = titre ;}
    void setDesc(string desc) {this->description = desc; }
    void setAnnee(int annee) {this->anneeCreation = annee;}
    void initEnsemble(int n) { this->etatsPossibles = new EnsembleEtats(n) ;}
    EnsembleEtats* getEnsemble() {return etatsPossibles;};
    int getAnnee() const {return anneeCreation; }
    void chargerModele(FILE *f);//charge les �l�ments du fichier puis fait appel au constructeur
    void creerModele();//propose choix � l'utilisateur, g�n�re r�gles puis fait appel au constructeur
    void sauvegardeM();
    void appliquerTransition(const Configuration &dep, Configuration &dest) const;
};

#endif


