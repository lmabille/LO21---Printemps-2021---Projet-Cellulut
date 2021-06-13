/**
 * @file loadConfig.cpp
 * @author Thomas Guegan (you@domain.com)
 * @brief ensemble de fonctions permettant de charger des configurations
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "loadConfig.h"
#include <iostream>
#include "pugixml.hpp"
#include "Modele.h"

using namespace pugi;
using namespace std;


/**
 * @brief Récupération du nombre de configuration pour un modèle
 *
 * @param[in] adresse du fichier contenant le modèle et les configuraitons
 * @return valeur correspondant au nombre de configurations disponibles
 */

int getNbConfig(const char* nom_fichier) {
    xml_document doc;


    // load the XML file
    if (!doc.load_file(nom_fichier)){
        cout << "echec";
        return -1;
    }



    xml_node tools = doc.child("Modele").child("ListeConfig");


    int cpt = 0;


    for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it) { // on compte le nombre de configuration

        cpt ++ ;


    }


    return cpt;
}


/**
 * @brief Récupération de la liste de nom des configurations d'un modèle
 *
 * @param[in] adresse du fichier contenant le modèle et les configuraitons
 * @return tableau de string correspondant à la liste de nom des configurations
 */

string * getListeConfig(const char* nomFichier) {

    xml_document doc;


    // load the XML file
    if (!doc.load_file(nomFichier)){
        cout << "echec";
        return nullptr;
    }



    xml_node tools = doc.child("Modele").child("ListeConfig"); // on rentre dans la liste de configuration

    string* listeNom= new string [45]();
    int cpt = 0;


    for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it) {

        string tmp ;
        xml_node nom = it->child("Nom");


        tmp = nom.attributes_begin()->value();


        listeNom[cpt] = tmp; // on enregistre le nom de la configuration

        cpt ++ ;


    }

    cout << "Liste Config ok " <<endl;
    return listeNom;

}

/**
 * @brief Récupération de la configuration chargée
 *
 * @param[in] adresse du fichier contenant le modèle et les configuraitons
 * @param[in] nom de la configuration à charger
 *
 * @return pointeur sur la configuration chargée
 */
Configuration * chargerConfiguration(const char* nomFichier , string nomConfig) {

    xml_document doc;
    Configuration * config;
    // load the XML file
    if (!doc.load_file(nomFichier)){
        cout << "echec";
        return nullptr;
    }



    xml_node tools = doc.child("Modele").child("ListeConfig"); // on rentre dans la liste de configurations

    for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it) {

        string tmp ;
        xml_node nom = it->child("Nom");


        tmp = nom.attributes_begin()->value();

        if (tmp == nomConfig) {
            string nom;
            int x;
            int y;


            int cpt = 0;
            for (xml_node_iterator balise = it->begin(); balise != it->end(); balise ++) {


                if (cpt == 0) { //si on est dans la balise de nom
                   nom = balise->attributes_begin()->value();


                }
                if (cpt == 1) { // si on est dans la balise de taille
                    int delimitation = 0;
                    for (xml_attribute_iterator cp = balise->attributes_begin(); cp != balise->attributes_end(); ++cp) {// boucle pour recup X et Y

                        if (delimitation == 0) {

                            x = atoi(cp->value());
                            delimitation ++ ;
                        }
                        if (delimitation == 1) {
                            y = atoi(cp->value());

                        }





                    }






                }

                if (cpt == 2) { // si on est au niveau de la balise ensembleCase
                    Reseau res = Reseau(x,y);
                    config = new Configuration(res);
                    for ( xml_node_iterator case_lu = balise->begin(); case_lu != balise->end(); case_lu ++) { // on parcour toute les cases
                        int delimitation = 0;
                        int x,y,indice;
                        string label,couleur;


                        for (xml_attribute_iterator cp = case_lu->attributes_begin(); cp != case_lu->attributes_end(); ++cp) {// boucle pour recup les attributs

                            if (delimitation == 0) {
                                x = atoi(cp->value());

                            }
                            if (delimitation == 1) {
                                y = atoi(cp->value());

                            }
                            if (delimitation == 2) {
                                indice = atoi(cp->value());

                            }
                            if (delimitation == 3) {
                                label = cp->value();

                            }
                            if (delimitation == 4) {
                                couleur = cp->value();

                            }
                            delimitation ++ ;





                        }

                        Etat * e = new Etat(indice,label,couleur);
                        config->setEtatCellule(x,y,e);






                    }
                }
                cpt ++;
            }







            return  config; // on renvoit la configuration chargée

        }







    }



}
