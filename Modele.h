#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_MODELE_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_MODELE_H
#include <string>
#include <cstdio>
#include "voisinage.h"
#include "etat.h"
#include "configuration.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"

using namespace std;

string *generation_regles_Brians_Brain(const unsigned int nb_voisins, int &l);
string *generation_regles_Life_game(const unsigned int nb_voisins, int &l);
string *generation_regles_Griffeath(const unsigned int nb_voisins, int &l);
string *generation_regles_Wireworld(const unsigned int nb_voisins, int &l);
string *generation_regles_Langton_Loop(int &l);

class FonctionTransition
{
protected:
    string *tableau;
    unsigned int taille;
    friend class Modele;

public:
    FonctionTransition(string *tab) : tableau(tab), taille(0){};
    FonctionTransition(string *tab, unsigned int t) : tableau(tab), taille(t){};
    FonctionTransition() = default;
    string *getTableau() { return tableau; }
    void setTableau(string *tab) { this->tableau = tab; }
    void setTaille(unsigned int nb) { this->taille = nb; }
    unsigned int getTaille() const { return taille; }
    virtual char comparaison_voisinnage(string voisins, string *trans, char cel, unsigned int limit, int nb_Etat);
};

class FonctionTransitionIntention : public FonctionTransition
{
public:
    FonctionTransitionIntention(string *tab, unsigned int t) : FonctionTransition(tab, t){};
    char comparaison_voisinnage(string voisins, string *trans, char cel, unsigned int limit, int nb_Etat);
};

class Modele
{
    string titre;                  //key
    EnsembleEtats *etatsPossibles; // � prendre en compte dans les constructeurs/ destructeurs!
    FonctionTransition *fonctionTrans;
    Voisinage *typeVoisinnage;
    string typef; //type de la fonction de transition : intension ou extension
    string description;
    string auteur;
    unsigned int anneeCreation;
    friend class Simulateur;

public:
    Modele();
    Modele(string t, EnsembleEtats *e, FonctionTransition *f, string typeFonction, Voisinage *v, string d, string a = "", unsigned int annee = 0) : titre(t), etatsPossibles(e), fonctionTrans(f), typef(typeFonction), typeVoisinnage(v), description(d), auteur(a), anneeCreation(annee) {}
    Modele(EnsembleEtats *e, FonctionTransition *f, string typeFonction, Voisinage *v) : etatsPossibles(e), fonctionTrans(f), typef(typeFonction), typeVoisinnage(v) {}
    ~Modele() { delete[] etatsPossibles; } // pas s�r de �a // + voir le destructeur de la classe EnsembleEtats
    const string &getTitre() const { return titre; }
    EnsembleEtats *getEtatsPossibles() const { return etatsPossibles; }
    const FonctionTransition &getFonctionTransition() const { return *fonctionTrans; }
    Voisinage *getVoisin() const { return typeVoisinnage; }
    const string &getDescription() const { return description; }
    const string &getAuteur() const { return auteur; }
    const string &getTypeFonction() const { return typef; }
    FonctionTransition *getFonction() { return fonctionTrans; }
    void setAutheur(string nom) { this->auteur = nom; }
    void setTitre(string titre) { this->titre = titre; }
    void setDesc(string desc) { this->description = desc; }
    void setAnnee(int annee) { this->anneeCreation = annee; }
    void initEnsemble(int n) { this->etatsPossibles = new EnsembleEtats(n); }
    void setTypef(string type) { this->typef = type; }
    EnsembleEtats *getEnsemble() { return etatsPossibles; };
    void setFonction(FonctionTransition * f) {this->fonctionTrans = f;}
    int getAnnee() const { return anneeCreation; }
    //  void chargerModele(FILE *f); //charge les �l�ments du fichier puis fait appel au constructeur
    void creerModele(); //propose choix � l'utilisateur, g�n�re r�gles puis fait appel au constructeur
    void sauvegardeM();
    void appliquerTransition(const Configuration &dep, Configuration &dest) const;
};

#endif
