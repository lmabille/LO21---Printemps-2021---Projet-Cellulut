//
// Created by thoma on 07/06/2021.
//

#include "loadConfig.h"
#include <iostream>
#include "pugixml.hpp"
#include "Modele.h"

using namespace pugi;
using namespace std;

string * getListeConfig(const char* nomFichier) {

    xml_document doc;

    // load the XML file
    if (!doc.load_file(nomFichier)){
        cout << "echec";
        return nullptr;
    }

    Modele* charge = new Modele;

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