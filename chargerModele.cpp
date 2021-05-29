//
// Created by thoma on 25/05/2021.
//

#include "chargerModele.h"
#include <iostream>
#include "pugixml.hpp"
#include "Modele.h"

using namespace pugi;
using namespace std;


Modele* chargerModel(const char *nomFichier) {
    cout << "\nParsing file.....\n\n";

    xml_document doc;

    // load the XML file
    if (!doc.load_file(nomFichier)){
        cout << "echec";
        return nullptr;
    }

    Modele* charge = new Modele;

    xml_node tools = doc.child("Modele");


    for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it) {
        cout << it->name() << " : " ;

        string tmp = it->name();
        string val;

        for (xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait) {
            cout  << ait->value();
            val = ait->value();
        }

        if (tmp == "Auteur") {
            charge->setAutheur(val);
        }
        if (tmp == "titre") {
            charge->setTitre(val);
        }
        if (tmp == "Description") {
            charge->setDesc(val);
        }
        if (tmp == "AnneeCreation") {
            charge->setAnnee(stoi(val));
        }

        if (tmp == "Etat") {
            cout <<endl;



            Etat * liste = new Etat[15] ();
            int n=0;

            xml_node test = tools.child("Etat");
            for (xml_node_iterator it2 = test.begin(); it2 != test.end(); ++it2) {

                cout << it2->name() << " : ";
                string nom = it2->name();
                for (xml_attribute_iterator cpt = it2->attributes_begin(); cpt != it2->attributes_end(); ++cpt) {
                    cout  << cpt->value() ;
                    val = cpt->value();
                }

                if (nom == "NombreEtat") {
                    //cout << stoi(val);
                    charge->initEnsemble(stoi(val));
                }
                if (nom == "Label") {
                    liste[n].setlabel(val);
                }
                cout <<endl;
            }
            charge->getEnsemble()->setListe(liste);
        }

        if (tmp == "Voisinage") {
            cout << endl;

            xml_node test = tools.child("Voisinage");
            string name = test.begin()->attributes_begin()->value();
            cout << "NOm : " << name << endl;
            charge->getVoisin().

            test = test.child("Element");

            Case* liste_voisin = new Case[10]();


            for (xml_node_iterator it2 = test.begin(); it2 != test.end(); ++it2) {

                cout << it2->name() << ": ";
                string nom = it2->name();

                int x_y_test = 0;
                int x = 0;
                int y = 0;
                int nbVoisin =0;
                for (xml_attribute_iterator cpt = it2->attributes_begin(); cpt != it2->attributes_end(); ++cpt) {



                    cout << cpt->value() << " " ;
                    val = cpt->value();
                    if (x_y_test == 0){
                        x = stoi(val);
                        x_y_test ++;
                    }
                    if (x_y_test == 1) {
                        y = stoi(val);

                    }

                    liste_voisin[nbVoisin] = Case(x,y);

                }



                cout << endl;
            }

            charge->getVoisin()->setensemble_case(liste_voisin);


        }

        cout << endl;
    }

    cout << endl;

    //cout << charge->getAuteur();

    return charge;

}