/**
 * @file etat_reseau.cpp
 * @author Orhane Lahneche 
 * @brief 
 * @version 0.1
 * @date 2021-06-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "etat_reseau.h"
/**
 * @brief setteur de l'attribut etat
 * 
 * @param e nouvelle etat
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
