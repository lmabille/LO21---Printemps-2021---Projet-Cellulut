#include<string>
#include<cstdio>

using namespace std;

class Voisinage{

};

class Etat{
    string label;

public :
    const string& getLabel() const { return label; }


};

bool operator!=(const Etat& e1, const Etat& e2);


class Modele{
    string titre; //key
    Etat **ensembleEtat;
    string regles[1000];
    Voisinnage *typeVoisinnage;
    string description;
    string auteur;
    unsigned int anneeCreation;

public :
    Modele(string t, Etat **e, string r[1000], Voisinnage *v, string d, string a="",unsigned int annee=0):titre(t), ensembleEtat(e), regles(r), typeVoisinnage(v), description(d), auteur(a), anneeCreation(annee){}
    ~Modele(){
        delete[] ensembleEtat;
    }
    const string& getTitre() const {return titre; }
    Etat ** const getEtat() const {return ensembleEtat;}
     const string& getRegles() const {return regles; }
    const Voisinnage *getVoisin() const {return typeVoisinnage; }
    const string& getDescription() const {return description; }
    const string& getAuteur() const {return auteur; }
    int getAnnee() const {return anneeCreation; }
    void chargerModele(FILE *f);//charge les éléments du fichier puis fait appel au constructeur
    void creerModele();//propose choix à l'utilisateur, génère règles puis fait appel au constructeur
    FILE *sauvegarderModele();//sauvegarde l'ensemble des attributs dans un fichier xml


};




