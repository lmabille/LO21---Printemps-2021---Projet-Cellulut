/**
 * @file voisinage.cpp
 * @author Thomas Guegan & Violette Durocher
 * @brief Fichier decrivant les fonctions relatives aux voisinages et a leur ensemble de cases.
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "voisinage.h"
#include <vector>
#include <algorithm>


/**
 * @brief Construit l'ensemble de cases de la classe Voisinage a partir d'un vecteur de cases.
 *
 * @param[in] tableau Vecteur de cases
 * @return   void
 */
void Voisinage::setensemble_case(std::vector<Case> tableau)
{
    nbCelluleVoisi = tableau.size();

    if (ensemble_case == nullptr) std::cout<<"bah c nul enft"<<endl;
    if (ensemble_case != nullptr)
    {
        std::cout<<"PASNUL"<<endl;
        delete[] ensemble_case;
        std::cout <<"bien detruit"<<endl;
    }

    ensemble_case = new Case[nbCelluleVoisi];
    for (unsigned int i = 0; i < tableau.size(); i++)
    {
            ensemble_case[i] = tableau[i];
    }
}


/**
 * @brief Construit l'ensemble de cases de la classe Voisinage a partir d'un pointeur sur un tableau de cases.
 *
 * @param[in] tableau Pointeur sur le tableau de cases
 * @return   void
 */
void Voisinage::setensemble_case(Case* tableau)
{
    this->ensemble_case = tableau;
}


/**
 * @brief Redefinition de la fonction definir_ensemble_case de la classe abstraite Voisinage adaptee au voisinage de Von Neumann
 *
 * @param[in] rayon Rayon de definition du voisinage
 * @return   void
 */
void V_VonNeumann::definir_ensemble_case(int rayon)
{

    vector<Case> tableau;
    int ligneMiddleCell = 0;
    int colonneMiddleCell = 0;

    if (rayon ==1) // tri en escargot nécessaire pour le déroulement de langston loop
    {
        tableau.push_back(Case(-rayon,0));
        tableau.push_back(Case(0,rayon));
        tableau.push_back(Case(rayon,0));
        tableau.push_back(Case(0,-rayon));
    }

    else // le tri en escargot n'est pas nécessaire, on s'appuie sur la formule du Voisinage de Von Neumann generalise au rayon r
    {
        for (int r=1; r<=rayon;r++)
        {
            for (int i = -r; i<=r; i++)
            {
                for (int j = -r; j<=r; j++)
                {
                    if (i!=ligneMiddleCell || j!=colonneMiddleCell)
                    {
                        if ((abs(i) + abs(j))<=r)
                        {
                            tableau.push_back(Case(i,j));
                        }
                    }
                }
            }
        }
    }

    nbCelluleVoisi = tableau.size();
    ensemble_case = new Case[nbCelluleVoisi];
    this->setensemble_case(tableau);
    tableau.clear();
}


/**
 * @brief Redefinition de la fonction definir_ensemble_case de la classe abstraite Voisinage adaptee au voisinage de Moore
 *
 * @param[in] rayon Rayon de definition du voisinage
 * @return   void
 */
void V_Moore::definir_ensemble_case(int rayon)
{
    nbCelluleVoisi = (2*rayon +1)*(2*rayon +1) - 1;

    ensemble_case = new Case[nbCelluleVoisi]; // on réserve la place pour le bon nombre de cellules

    int ind = 0;

    for (int r=1; r<= rayon; r++)
    {
        // ligne du haut (coins inclus)
        for (int j=-r; j<=r; j++)
        {
            ensemble_case[ind].setL_C(r,j);
            ind++;
        }
        // ligne de droite (coins exclus)
        for (int i=r-1; i>=-r+1; i--)
        {
            ensemble_case[ind].setL_C(i,r);
            ind++;
        }
        // ligne du bas (coins inclus)
        for (int j=r; j>=-r; j--)
        {
            ensemble_case[ind].setL_C(-r,j);
            ind++;
        }
        // ligne de gauche (coins exclus)
        for (int i=-r+1; i<=r-1; i++)
        {
            ensemble_case[ind].setL_C(i,-r);
            ind++;
        }
    }
}


/**
 * @brief Retourne le nombre de cellules voisines
 *
 * @return   le nombre de cases de ensemble_cases
 */
size_t Voisinage::getNbCelluleVoisi() const
{
    return this->nbCelluleVoisi;
}


/**
 * @brief Retourne le nom du voisinage
 *
 * @return   l'attribut typeVoisi
 */
const string Voisinage::getTypeVoisi()
{
    return this->typeVoisi;
}


/**
 * @brief Retourne le tableau de cases contenant les coordonnees des cellules a prendre en compte dans le voisinage
 *
 * @return   l'attribut tableau de cases ensemble_case
 */
Case *Voisinage::getTableau()
{
    return this->ensemble_case;
}


/**
 * @brief Retourne le tableau de cases contenant les coordonnees des cellules a prendre en compte dans le voisinage
 *
 * @return   l'attribut tableau de cases ensemble_case
 */
Case &Voisinage::operator[](int indice)
{
    try
    {
        if (indice < 0 || indice >= nbCelluleVoisi)
            throw string("case n'existe pas !"); // à remplacer par AutomateException comme dans le td
        else
            return ensemble_case[indice];
    }
    catch (string const &erreur)
    {
        cout << erreur << endl;
    }
}




