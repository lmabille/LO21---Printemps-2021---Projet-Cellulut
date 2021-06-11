//
// Created by thoma on 13/05/2021.
//

#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_VOISINAGE_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_VOISINAGE_H

using namespace std;
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

class Case
{ // Classe case
    int l;
    int c;
    void setL(int newL) { this->l = newL; }
    void setC(int newC) { this->c = newC; }
    void setL_C(int newL, int newC) {this->l = newL; this->c = newC;}
    friend class Voisinage;
    friend class V_VonNeumann;
    friend class V_Moore;
    friend class V_ChoixUtilisateur;

public:
    Case() = default;
    int getL() const { return l; };
    int getC() const { return c; };
    Case(int L, int C) : l(L), c(C){};
};

class Voisinage // classe abstraite
{
private:
    string typeVoisi; // nom du voisinage

protected:
    size_t nbCelluleVoisi; // nb de cellules prises en compte
    Case *ensemble_case; // tableau de coordonnées des cellules voisines
    friend class Modele;

public:

    // constructeurs pour une classe abstraite?
    Voisinage() = default;
    Voisinage(int n);
    ~Voisinage() {delete[] ensemble_case;}

    const string getTypeVoisi(); // non virtual
    size_t getNbCelluleVoisi() const; // non virtual
    void setNbCellule(int nb) {this->nbCelluleVoisi = nb;};
    void setensemble_case(Case *c) {this->ensemble_case = c; };
    void setType(string t) { typeVoisi = t; }

    Case *getTableau(); // non virtual
    Case &operator[](int indice); // non virtual

    virtual void definir_ensemble_case(int rayon) = 0; // Neumann et Moore de base peuvent être considérés comme des spécialisations avec un rayon 1/ L'utilisateur choisi le rayon max dans lequel il veut sélectionner ses cellules voisines.
    virtual void ajouter_case(size_t i, size_t j) = 0;
};

class V_VonNeumann: public Voisinage
        /* Ce voisinage prend en compte les cellules adjacentes horizontalement et verticalement.
         * Il peut être généralisé avec un rayon r, donc on considèrera que le premier cas est
         * une spécialisation du cas général, c'est-à-dire avec un rayon 1.*/
{
public:
   // V_VonNeumann(int rayon = 1): Voisinage(){}
    void definir_ensemble_case(int rayon = 1) override;
    void ajouter_case(size_t i, size_t j) override {}
};

class V_Moore: public Voisinage
{
public:
    void definir_ensemble_case(int rayon = 1) override;
    void ajouter_case(size_t i, size_t j) override {}
};

class V_ChoixUtilisateur: public Voisinage
{
public:
    // V_ChoixUtilisateur(int n);
    void definir_ensemble_case(int rayon = 1) override {}
    void ajouter_case(size_t i, size_t j) override;
};



#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_VOISINAGE_H
