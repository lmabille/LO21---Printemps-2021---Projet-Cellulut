//
// Created by thoma on 07/06/2021.
//

#include "loadConfig.h"
#include <iostream>
#include "pugixml.hpp"
#include "Modele.h"

using namespace pugi;
using namespace std;

int getNbConfig(const char* nom_fichier) {
    xml_document doc;


    // load the XML file
    if (!doc.load_file(nom_fichier)){
        cout << "echec";
        return -1;
    }



    xml_node tools = doc.child("Modele").child("ListeConfig");


    int cpt = 0;


    for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it) {

        cpt ++ ;


    }


    return cpt;
}


string * getListeConfig(const char* nomFichier) {

    xml_document doc;


    // load the XML file
    if (!doc.load_file(nomFichier)){
        cout << "echec";
        return nullptr;
    }



    xml_node tools = doc.child("Modele").child("ListeConfig");

    string* listeNom= new string [15]();
    int cpt = 0;
    //string tmp ;

    for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it) {
        //cout << it->name() <<endl;
        string tmp ;
        xml_node nom = it->child("Nom");

        //for (xml_attribute_iterator ait = nom.attributes_begin(); ait != nom.attributes_end(); ++ait) {
            //cout << nom.attributes_begin()->value()<< endl;
            tmp = nom.attributes_begin()->value();
        //}

        listeNom[cpt] = tmp;
        //cout << listeNom[cpt]<< endl;
        cpt ++ ;


    }

    cout << "Liste Config ok " <<endl;
    return listeNom;

}


Configuration * chargerConfiguration(const char* nomFichier , string nomConfig) {

    xml_document doc;
    Configuration * config;
    // load the XML file
    if (!doc.load_file(nomFichier)){
        cout << "echec";
        return nullptr;
    }

    cout << "lance " <<endl;

    xml_node tools = doc.child("Modele").child("ListeConfig");

    for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it) {
        //cout << it->name() <<endl;
        string tmp ;
        xml_node nom = it->child("Nom");


        tmp = nom.attributes_begin()->value();

        if (tmp == nomConfig) {
            string nom;
            int x;
            int y;

            cout << "ok : " << nomConfig << " : " << tmp << endl;
            int cpt = 0;
            for (xml_node_iterator balise = it->begin(); balise != it->end(); balise ++) {
                cout << balise->name() <<endl;

                if (cpt == 0) {
                   nom = balise->attributes_begin()->value();
                   cout << " ---" <<nom << endl;

                }
                if (cpt == 1) {
                    int delimitation = 0;
                    for (xml_attribute_iterator cp = balise->attributes_begin(); cp != balise->attributes_end(); ++cp) {

                        if (delimitation == 0) {

                            x = atoi(cp->value());
                            delimitation ++ ;
                        }
                        if (delimitation == 1) {
                            y = atoi(cp->value());

                        }

                        cout << cp->value() << " " <<endl ;
                        //val = cp->value();



                    } // boucle pour recup X et Y

                    cout << " ----" << x << " " << y <<endl;




                }

                if (cpt == 2) {
                    Reseau res = Reseau(x,y);
                    config = new Configuration(res);
                    for ( xml_node_iterator case_lu = balise->begin(); case_lu != balise->end(); case_lu ++) {
                        int delimitation = 0;
                        int x,y,indice;
                        string label,couleur;


                        for (xml_attribute_iterator cp = case_lu->attributes_begin(); cp != case_lu->attributes_end(); ++cp) {

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

                            //val = cp->value();



                        } // boucle pour recup les attributs
                        cout << x << " "<< y << " " << indice << " " << label << " " << couleur<< " "<<endl ;
                        Etat * e = new Etat(indice,label,couleur);
                        config->setEtatCellule(x,y,e);






                    }
                }
                cpt ++;
            }

            //Configuration* config = new Configuration;





            return  config;

        }


        //}




    }



}
