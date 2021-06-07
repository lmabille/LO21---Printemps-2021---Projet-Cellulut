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

    xml_node tools = doc.child("Modele").child("");


    for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it) {


}