/**
 * @file configuration.cpp
 * @author Violette Durocher/Orhane Lahneche/ Laurine Hamard (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */



#include <iostream>
#include "configuration.h"
#include "etat_reseau.h"
#include "pugixml.hpp"
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace pugi;

/*** Classe Configuration ***/
/**
 * @brief Retourne le voisinage d'une case
 *
 * @param[in] ligne de la case
 * @param[in] colonne de la case
 * @param[in] type du voisinage
 * @return   chaîne de caractère représentant le voisinage
 */
string Configuration::getVoisinage(int i, int j, Voisinage& typeVoisi) const
{
    /* pour chaque élément du tableau ensemble de cases,
       récupère le déplacement relatif en ligne et en colonne en fonction du voisinage passé en argument,
       puis récupère l'état de la cellule i+ligneRel, j+colRel, stocke cet état
       dans un tableau de caractères, retourne ce tableau */

    string voisinage;
    int ligneRel,colRel;
    int indice;
    int ligne=0, colonne=0;
    for (int c = 0; c < typeVoisi.getNbCelluleVoisi(); c++)
    {
        ligneRel = typeVoisi[c].getL();
        colRel = typeVoisi[c].getC();
        //calcule des coordonnées en prenant en compte que le modulo peut renvoyer des nombres négatifs
        if (((i+ligneRel)%getReseauLignes())<0) ligne = ((i+ligneRel)%getReseauLignes()) + getReseauLignes();
        else ligne = (i+ligneRel)%getReseauLignes();

        if (((j+colRel)%getReseauColonnes())<0) colonne = ((j+colRel)%getReseauColonnes()) + getReseauColonnes();
        else colonne = (j+colRel)%getReseauColonnes();

        indice = getEtatCellule(ligne,colonne).getIndice();
        voisinage += to_string(indice);
        //cout << "test OK" << endl;
    }
    return voisinage;
}

/**
 * @brief Constructeur de la classe configuration
 *
 * @param[in] Réseau
 * @return   nouvelle configuration
 */

Configuration::Configuration(const Reseau &r): reseau(r)
/* Initialise simplement une grille de cellules avec les bonnes dimensions (se charge des allocations mémoire) */
{
    // Allocation mémoire
    grille = new Cellule* [r.nb_lignes];
    for (unsigned int i=0; i<r.nb_lignes; i++)
    {
        *(grille+i) = new Cellule[r.nb_colonnes];
    }
}

/**
 * @brief Constructeur de la classe configuration, initialise la configuration avec les états d'indices 0
 *
 * @param[in] Réseau
 * @param[in] un ensemble d'état possible
 * @return   nouvelle configuration
 */

Configuration::Configuration(const Reseau &r, EnsembleEtats& etatsPossibles): reseau(r)
// Initialise une grille de cellule et met par d?faut toutes les cellules ? l'?tat 0 du tableau d'?tats possible
{
    // Allocation m?moire
    grille = new Cellule* [r.nb_lignes];
    for (unsigned int i=0; i<r.nb_lignes; i++)
    {
        *(grille+i) = new Cellule[r.nb_colonnes];
    }
    // remplissage avec l'?tat[0] par d?faut
    for (unsigned int i=0; i<r.nb_lignes; i++)
    {
        for (unsigned int j = 0; j<r.nb_colonnes; j++)
        {
            grille[i][j].set_etatcellule(&(etatsPossibles.getListe()[0])); //modification de l'overload "[]" pour utiliser l'indice
        }
    }
}

/**
 * @brief remplis une configuration de façon aléatoire
 *
 * @param[in] un ensemble d'état possible
 * @return  void
 */

void Configuration::remplissageAleatoire(EnsembleEtats& etatsPossibles)
// Initialise une grille de cellule et choisit un ?tat al?atoirement pour chaque cellule
{
    unsigned int indiceAleatoire = 0;

    for (unsigned int i=0; i<reseau.nb_lignes; i++)
    {
        for (unsigned int j = 0; j<reseau.nb_colonnes; j++)
        {
            indiceAleatoire = rand()%(etatsPossibles.getNombreEtats());
            grille[i][j].set_etatcellule(&(etatsPossibles.getListe()[indiceAleatoire]));
        }
    }
}

/**
 * @brief Constructeur de recopire pour la classe configuration
 * @param[in] une configuration
 * @return   nouvelle configuration
 */
Configuration::Configuration(const Configuration& c): reseau(c.reseau)
{

    grille = new Cellule* [reseau.nb_lignes];
    for (unsigned int i=0; i<reseau.nb_lignes; i++)
    {
        *(grille+i) = new Cellule[reseau.nb_colonnes];
    }
}
/**
 * @brief Destructeur de la classe configuration
 */
Configuration::~Configuration()
{
    for (size_t i = 0; i<reseau.nb_lignes; i++)
    {
        delete[] grille[i];
    }
    delete[] grille;
}

/**
 * @brief Surcharge de l'opérateur =
 *  @param[in] une configuration
 *  @return   nouvelle configuration
 */
Configuration& Configuration::operator=(const Configuration& c)
{
    if (this != &c)
    {
        reseau = c.reseau;
        Cellule** newGrille = new Cellule* [reseau.nb_lignes];
        for (unsigned int i=0; i<reseau.nb_lignes; i++)
        {
            *(newGrille+i) = new Cellule[reseau.nb_colonnes];
        }
        Cellule** oldGrille = grille;
        grille = newGrille;
        delete oldGrille;

        for (size_t i=0; i<reseau.nb_lignes; i++)
        {
            for (size_t j=0; j<reseau.nb_colonnes; j++)
            {
                grille[i][j] = newGrille[i][j];
            }
        }
    }
    return *this;
}

/**
 * @brief sauvegarde la configuration
 *  @param[in] le titre du modèle dans lequel enregistrer la configuration
 *  @return   void
 */
void Configuration::sauvegarderConfiguration(string titreMdodele) const {
    //On va chercher le modèle avec le titre
    xml_document doc;
    string xmlFilePath = "../LO21---Printemps-2021---Projet-Cellulut/Modeles/";
    xmlFilePath += titreMdodele;
    xmlFilePath += ".xml";
    xml_parse_result result = doc.load_file(xmlFilePath.c_str(),parse_default|parse_declaration);
    if (!result)
    {
        cout << "Impossible de trouver le modele";
        return;
    }

    xml_node modele = doc.document_element();
  //  xml_node configs = modele.append_child("ListeConfig");
    xml_node configs = modele.child("ListeConfig");

    //on récupère le nombre de configuration du modèle
     string nomConfig="Configuration";
    int t= stoi(configs.attribute("nombre").value());
     t++;
     string te = to_string(t);
     nomConfig += te;
     configs.attribute("nombre").set_value(t);
     //modifier la valeur de l'attribut

//On insère la configuration
    xml_node config = configs.append_child("Configuration");
    xml_node nomC = config.append_child("Nom");
    nomC.append_attribute("name")=nomConfig.c_str();
    unsigned int m = this->getReseauLignes();
    unsigned int n = this->getReseauColonnes();
    xml_node tailleReseau = config.append_child("Taille");
    tailleReseau.append_attribute("lignes")=m;
    tailleReseau.append_attribute("colonnes")=n;
    xml_node cellulesE = config.append_child("EnsembleCase");
    for(size_t i=0; i<m; i++){
        for(size_t j=0; j<n; j++){

            Etat& e = getEtatCellule (i, j);
            xml_node cellule = cellulesE.append_child("Case");
            cellule.append_attribute("X")=i;
            cellule.append_attribute("Y")=j;
            cellule.append_attribute("Indice")=e.getIndice();
            cellule.append_attribute("Label")=e.getLabel().c_str();
            cellule.append_attribute("Couleur")=e.getCouleur().c_str();





        }


    }

    bool saveSuccess = doc.save_file(xmlFilePath.c_str(), PUGIXML_TEXT("   "));



    cout<<saveSuccess;


}

