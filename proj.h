#include<string>

using namespace std;

class Voisinnage{

};

class Etat{
    string label;

public :
    const string& getLabel() const { return label; }


};

bool operator!=(const Etat& e1, const Etat& e2);

class Fonction_Transition{ //classe abstraite
protected :
    int id;
    Etat **etatAutorise;
public :
    int getId() const {return id; }
    Etat ** const getEtat() const {return etatAutorise;} // assez sécurisé

};

class Modele{
    string titre; //key
    Etat **ensembleEtat;
    Fonction_Transition *fonction;
    Voisinnage *typeVoisinnage;
    string description;
    string auteur;
    unsigned int anneeCreation;

public :
    Modele(string t, Etat **e, Fonction_Transition *f, Voisinnage *v, string d, string a="",unsigned int annee=0):titre(t), ensembleEtat(e), fonction(f), typeVoisinnage(v), description(d), auteur(a), anneeCreation(annee){}
    ~Modele(){
        delete[] ensembleEtat;
    }
    bool verificationEtat();
    const string& getTitre() const {return titre; }
    Etat ** const getEtat() const {return ensembleEtat;}
    const Fonction_Transition *getFonction() const {return fonction; }
    const Voisinnage *getVoisin() const {return typeVoisinnage; }
    const string& getDescription() const {return description; }
    const string& getAuteur() const {return auteur; }
    int getAnnee() const {return anneeCreation; }







};


class TypeFonction : Fonction_Transition{ //sous_classe regroupant les grandes familles de fonctions en fct de leur règles de transitions
public :
    TypeFonction(int id, Etat **e);//à implémenter plus tard
    ~TypeFonction(){
        delete[] etatAutorise;
    }
    appliquerTransition(const Etat& dep, const Etat& arr); //à implémenter plus tard


};


