#include <iostream>
#include "configuration.h"
#include "etat_reseau.h"
#include "pugixml.hpp"
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace pugi;

/*** Classe Configuration ***/

string Configuration::getVoisinage(int i, int j, Voisinage& typeVoisi) const // � tester
{
    /* pour chaque �l�ment du tableau ensemble de cases,
       r�cup�re le d�placement relatif en ligne et en colonne en fonction du voisinage pass� en argument,
       puis r�cup�re l'�tat de la cellule i+ligneRel, j+colRel, stocke cet �tat
       dans un tableau de caract�res, retourne ce tableau */

    string voisinage;
    int ligneRel,colRel;
    int indice;
    int ligne=0, colonne=0;
    for (int c = 0; c < typeVoisi.getNbCelluleVoisi(); c++)
    {
        ligneRel = typeVoisi[c].getL();
        colRel = typeVoisi[c].getC();
        //calcule des coordonn�es en prenant en compte que le modulo peut renvoyer des nombres n�gatifs
        if ((i+ligneRel)%reseau.nb_lignes<0) ligne = (i+ligneRel)%reseau.nb_lignes + reseau.nb_lignes;
        else ligne = (i+ligneRel)%reseau.nb_lignes;
        if ((j+colRel)%reseau.nb_colonnes<0) colonne = (j+colRel)%reseau.nb_colonnes + reseau.nb_colonnes;
        else colonne = (j+colRel)%reseau.nb_colonnes;
        //cout << "coordonnees du voisin " << c << " : " << endl;
        //cout << "\tligne : " << ligne << "\n" << "\tcolonne : " << colonne << endl;
        indice = getEtatCellule(ligne,colonne).getIndice();
        voisinage += to_string(indice);
        //cout << "test OK" << endl;
    }
    return voisinage;
}

Configuration::Configuration(const Reseau &r): reseau(r)
/* Initialise simplement une grille de cellules avec les bonnes dimensions (se charge des allocations m�moire) */
{
    // Allocation m�moire
    grille = new Cellule* [r.nb_lignes];
    for (unsigned int i=0; i<r.nb_lignes; i++)
    {
        *(grille+i) = new Cellule[r.nb_colonnes];
    }
}

/*
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
*/

// constructeur d'une configuration al?atoire (? d?placer dans une classe h?rit?e potentiellement)/ ou ? red?finir en temps que m?thode

Configuration::Configuration(const Reseau &r, EnsembleEtats& etatsPossibles): reseau(r)
// Initialise une grille de cellule et choisit un ?tat al?atoirement pour chaque cellule
{
    unsigned int indiceAleatoire = 0;

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
            indiceAleatoire = rand()%(etatsPossibles.getNombreEtats());
            grille[i][j].set_etatcellule(&(etatsPossibles.getListe()[indiceAleatoire]));
        }
    }
}


Configuration::Configuration(const Configuration& c): reseau(c.reseau)
{
    // reseau = c.reseau;
    grille = new Cellule* [reseau.nb_lignes];
    for (unsigned int i=0; i<reseau.nb_lignes; i++)
    {
        *(grille+i) = new Cellule[reseau.nb_colonnes];
    }
}

Configuration::~Configuration()
{
    for (int i = 0; i<reseau.nb_lignes; i++)
    {
        delete[] grille[i];
    }
    delete[] grille;
}

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
        /*for (int i = 0; i<reseau.nb_lignes; i++)
        {
            delete[] oldGrille[i];
        }*/
        //delete[] oldGrille;
        // remplissage ? n�cessaire ou pas ?
        for (int i=0; i<reseau.nb_lignes; i++)
        {
            for (int j=0; j<reseau.nb_colonnes; j++)
            {
                grille[i][j] = newGrille[i][j];
            }
        }
    }
    return *this;
}

void Configuration::sauvegarderConfiguration(string titreMdodele) const {
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

    xml_node modele = doc.document_element();//j'esp�re que �a r�cup bien le mod�le
  //  xml_node configs = modele.append_child("ListeConfig");
    xml_node configs = modele.child("ListeConfig");

    //on r�cup�re le nombre de configuration du mod�le
     string nomConfig="Configuration";
    int t= stoi(configs.attribute("nombre").value());
     t++;
     string te = to_string(t);
     nomConfig += te;
     configs.attribute("nombre").set_value(t);
     //modifier la valeur de l'attribut


    xml_node config = configs.append_child("Configuration");
    xml_node nomC = config.append_child("Nom");
    nomC.append_attribute("name")=nomConfig.c_str();
    unsigned int m = this->getReseauLignes();
    unsigned int n = this->getReseauColonnes();
    xml_node tailleReseau = config.append_child("Taille");
    tailleReseau.append_attribute("lignes")=m;
    tailleReseau.append_attribute("colonnes")=n;
    xml_node cellulesE = config.append_child("EnsembleCase");
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){

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
    //On augmente le nombre de config du mod�le :


    cout<<saveSuccess;


}

