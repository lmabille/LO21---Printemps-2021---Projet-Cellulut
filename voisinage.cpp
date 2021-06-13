/**
 * @file voisinage.cpp
 * @author Thomas Guegan / Violette Durocher (you@domain.com)
 * @brief fonctions de la classe Voisinage
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
 * @brief Fonction permettant de définir l'ensemble de case
 *
 * @param[in] tableau de cases
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

void Voisinage::setensemble_case(Case* tableau)
{
    this->ensemble_case = tableau;
}


/**
 * @brief définition du voisinage de VonNeuman
 *
 * @param[in] rayon
 */
void V_VonNeumann::definir_ensemble_case(int rayon)
{

    vector<Case> tableau;
    int ligneMiddleCell = 0;
    int colonneMiddleCell = 0; // test
    std::cout << "cellule du milieu : "<<ligneMiddleCell<<","<<colonneMiddleCell<<endl;

    if (rayon ==1) // bien trié pour langston loop
    {
        tableau.push_back(Case(-rayon,0));
        tableau.push_back(Case(0,rayon));
        tableau.push_back(Case(rayon,0));
        tableau.push_back(Case(0,-rayon));
    }

    else
    {
        for (int r=1; r<=rayon;r++)
        {
            std::cout<<"test rayon "<< r<<endl;

            for (int i = -r; i<=r; i++)
            {
                std::cout<<"ligne "<<i<<endl;
                for (int j = -r; j<=r; j++)
                {
                    std::cout<<"\tcolonne "<<j<<endl;
                    if (i!=ligneMiddleCell || j!=colonneMiddleCell)
                    {
                        std::cout <<"\t"<<i<<","<<j<<endl;
                        std::cout << "calcul coordonnee : "<< abs(i)<<" "<< abs(j);
                        std::cout << ", result = " <<abs(i) + abs(j)<<endl;
                        if ((abs(i) + abs(j))<=r)
                        {
                            std::cout <<"\t bien enregistre"<<endl;
                            tableau.push_back(Case(i,j));
                        }
                        else std::cout <<"\t nik"<<endl;
                        //std::cout << tableau.end()->getL() << "," << tableau.end()->getC() << endl;
                    }
                    else std::cout <<"zarbi"<<endl;
                    //std::cout<<"yo 2" <<endl;
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
 * @brief définition du voisinage de Moore
 *
 * @param[in] rayon
 */
void V_Moore::definir_ensemble_case(int rayon)
{
    nbCelluleVoisi = (2*rayon +1)*(2*rayon +1) - 1;


    ensemble_case = new Case[nbCelluleVoisi]; // on réserve la place pour le bon nombre de cellules

    int ind = 0;

    for (int r=1; r<= rayon; r++)
    {

        for (int j=-r; j<=r; j++)
        {

            ensemble_case[ind].setL_C(r,j);

            ind++;
        }

        for (int i=r-1; i>=-r+1; i--)
        {

            ensemble_case[ind].setL_C(i,r);

            ind++;
        }

        for (int j=r; j>=-r; j--)
        {

            ensemble_case[ind].setL_C(-r,j);

            ind++;
        }

        for (int i=-r+1; i<=r-1; i++)
        {

            ensemble_case[ind].setL_C(i,-r);

            ind++;
        }

    }

}

/**
 * @brief getter Nombre de cellule
 *
 * @return nombre de cellule
 */
size_t Voisinage::getNbCelluleVoisi() const
{
    return this->nbCelluleVoisi;
}

/**
 * @brief getter Type Voisinage
 *
 * @return type du voisinage
 */
const string Voisinage::getTypeVoisi()
{
    return this->typeVoisi;
}


/**
 * @brief getter Tableau du voisinage
 *
 * @return tableau du voisinage
 */
Case *Voisinage::getTableau()
{
    return this->ensemble_case;
}


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




