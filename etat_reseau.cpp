//
// Created by Anne LAHNECHE on 05/05/2021.
//
/**
 * @file etat_reseau.cpp
 * @author Orhane
 * @brief
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "etat_reseau.h"

/**
 * @brief setter d'etat de cellule
 *
 * @param[in] nouvel etat
 */
void Cellule::set_etatcellule(Etat *e)
{
    etat = e;
}
/**
 * @brief redéfintiion de l'opérateur d'affectation entre deux objet reséau
 * 
 * @param c le nouveau réseau
 * @return Reseau& 
 */
Reseau &Reseau::operator=(const Reseau &c)
{
    nb_lignes = c.nb_lignes;
    nb_colonnes = c.nb_colonnes;
    return *this;
}
