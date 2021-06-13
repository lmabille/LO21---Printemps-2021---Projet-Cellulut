//
// Created by thoma on 13/05/2021.
//

/**
 * @file etat.cpp
 * @author Thomas
 * @brief
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "etat.h"
#include <string.h>

/**
 * @brief constructeur de la classe Etat
 *
 * @return Etat avec un label Null et un indice 0
 */
Etat::Etat()
{
    label = "";
    indice=0;
}


/**
 * @brief fonction accesseurs du label de la classe
 *
 * @return label de l'objet utilisé
 */
string Etat::getLabel()
{
    return this->label;
}

void EnsembleEtats::definirEtats()
{
    int num;
    string lab;
    // + couleur
    for (int i=0; i<nombreEtats; i++)
    {
        cout << "Definition de l'etat " << i << " :\n";
        cout << "\tNumero: ";
        cin >> num; // check que ce soit bien un integer
        cout << "\tLabel: ";
        cin >> lab;
        // + couleur
        liste[i].setIndice(num);
        liste[i].setlabel(lab);
    }
}


/**
 * @brief surcharge de l'opérateur [] pour la classe EnsembeEtat
 *
 * @param[in] index indexe de l'état rechérché
 * @return un pointeur sur l'état recherché si il exite un pointeur null sinon
 */
Etat* EnsembleEtats::operator[](int index)
/* Permet de retourner un pointeur sur un état alors qu'ils sont stockés dans un tableau 1D */
{
    for (int i =0 ; i < nombreEtats ; i++)
    {
        if (liste[i].indice==index) return &liste[i];
    }

    cout << "etat n'existe pas\n";
    return nullptr;
}




