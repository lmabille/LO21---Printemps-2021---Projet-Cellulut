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
    //cout<<nomFichier<<"\n";

    xml_document doc;

    // load the XML file
    if (!doc.load_file(nomFichier)){
        cout << "echec";
        return nullptr;
    }

    Modele* charge = new Modele;

    xml_node tools = doc.child("Modele");


    for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it) {
        cout << it->name() << " : ";

        string tmp = it->name();
        string val;

        for (xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait) {
            cout << ait->value();
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

        if (tmp == "Etats") {
            cout <<endl;



            Etat * liste = new Etat[15] ();
            int n=0;

            xml_node test = tools.child("Etats");



            for (xml_node_iterator it2 = test.begin(); it2 != test.end(); ++it2) {
                string* lst_attri ;

                cout << it2->name() << " : ";

                string nom = it2->name();
                int indice =0;


                //cout << "je suis la "<<endl;

                int compteur =0;
                for (xml_attribute_iterator cpt = it2->attributes_begin(); cpt != it2->attributes_end(); ++cpt) {
                    cout  << cpt->value() ;
                    if (compteur !=0)
                    {
                        //cout <<"cocuou" <<cpt->value();
                        //indice = stoi(cpt->value());
                        compteur =0;
                    }
                    else{
                        val = cpt->value();
                        compteur ++;
                    }

                }

                if (nom == "NombreEtat") {
                    //cout << stoi(val);
                    charge->initEnsemble(stoi(val));
                }
                if (nom == "Etat") {
                    //cout << "je suis la" <<endl;
                    string label;
                    string couleur;
                    //int indice;
                    int v_cpt = 0;
                    for (xml_attribute_iterator cpt = it2->attributes_begin(); cpt != it2->attributes_end(); ++cpt) {
                        val = cpt->value();
                        if ( v_cpt == 0){
                            label = cpt->value();
                            cout << "LAbel ok " << label <<endl;
                            v_cpt ++;
                        }

                        else if ( v_cpt == 1) {
                            couleur = cpt->value();
                            v_cpt ++;
                        }

                        else if ( v_cpt == 2  ) {
                            cout << " :::: " << cpt->value() << endl;
                            //indice = 2;
                            indice = stoi(cpt->value());
                            /*
                            const char* test =  cpt->value() ;
                            int indi;
                            stringstream s(test);
                            s >> indi;
                            indice = indi;*/

                            v_cpt ++;
                        }


                        //cout<< cpt->name() << " : " << cpt->value() <<endl;
                    }


                    liste[n].setlabel(label);
                    liste[n].setIndice(indice);
                    liste[n].setCouleur(couleur);


                    n++;
                }
                cout <<endl;
            }

            cout << liste[0].getLabel() << liste[1].getLabel()<<endl;
            charge->getEnsemble()->setListe(liste);


        }
        //*/

        //
        if (tmp == "Voisinage") {
            cout << endl;

            xml_node test = tools.child("Voisinage");
            string name = test.begin()->attributes_begin()->value();
            cout << "NOm : " << name << endl;
            //charge->getVoisin().

            test = test.child("Element");


            int taille = 15;
            Case* liste_voisin = new Case[taille]();

            int nbVoisin =0;
            for (xml_node_iterator it2 = test.begin(); it2 != test.end() ; ++it2) {

                cout << it2->name() << ": ";
                string nom = it2->name();

                int x_y_test = 0;
                int x = 0;
                int y = 0;

                for (xml_attribute_iterator cpt = it2->attributes_begin(); cpt != it2->attributes_end(); ++cpt) {


                    cout << cpt->value() << " " ;
                    val = cpt->value();
                    if (x_y_test == 0){  //Si on est en train de lire la valeur de x
                        x = stoi(val);
                        x_y_test ++;
                    }
                    if (x_y_test == 1) { //Si on est en train de lire la valeur de y
                        y = stoi(val);

                    }


                }



                if (nbVoisin == taille) {
                    //cout << "augmentailee ok ";
                    Case* tempo = new Case[taille+15]();
                    for (int j =0; j< taille ; j++ ) {
                        tempo[j] = liste_voisin[j];
                    }
                    taille = taille + 15;
                    delete [] liste_voisin;
                    liste_voisin = tempo;

                }
                liste_voisin[nbVoisin] = Case(x,y);
                //cout <<"==>" << liste_voisin[nbVoisin].getL() << " " << liste_voisin[nbVoisin].getC() <<endl;
                nbVoisin++;
                cout << "NbVoisin :::" <<nbVoisin;



                cout << endl;
            }
            //cout <<"----->" << liste_voisin[0].getL()<<endl;
            //charge->getVoisin()->setNbCellule(nbVoisin);

            //Voisinage *cc = charge->getVoisin();

            charge->getVoisin()->setensemble_case(liste_voisin);
            charge->getVoisin()->setNbCellule(nbVoisin);


        }
        //*/

        if (tmp == "TypeFonctionTransition") {
            cout <<"----" << it->attributes_begin()->value();
            charge->setTypef(it->attributes_begin()->value());
            //charge->setAnnee(stoi(val));
        }


        if (tmp == "ListeRegle") {
            cout << "-----atteint";
            cout << endl;

            xml_node test = tools.child("ListeRegle");
            string name = test.begin()->attributes_begin()->value();
            cout << "NOm : " << name << endl;
            //charge->getVoisin().


            int taille = 15;
            string* liste_regle = new string[15]();

            int nbRegles =0;
            for (xml_node_iterator it2 = test.begin(); it2 != test.end() ; ++it2) {

                cout << it2->name() << ": ";
                string nom = it2->name();



                for (xml_attribute_iterator cpt = it2->attributes_begin(); cpt != it2->attributes_end(); ++cpt) {


                    cout << cpt->value() << " " ;
                    val = cpt->value();



                }



                if (nbRegles == taille) {
                    string* tempo = new string[taille*2]();
                    for (int j =0; j< taille ; j++ ) {
                        tempo[j] = liste_regle[j];
                    }
                    taille = taille *2;
                    delete [] liste_regle;
                    liste_regle = tempo;

                }

                liste_regle[nbRegles] = val;
                //cout <<"==>" << liste_voisin[nbVoisin].getL() << " " << liste_voisin[nbVoisin].getC() <<endl;
                nbRegles++;
                cout << "Nbregles :::" <<nbRegles;



                cout << endl;
            }
            //cout <<"----->" << liste_voisin[0].getL()<<endl;
            //charge->getVoisin()->setNbCellule(nbVoisin);
            charge->getFonction()->setTableau(liste_regle);
            charge->getFonction()->setTaille(nbRegles);



        }
        cout << endl;
    }

    //cout <<"----atteint aussi" << endl;



    //cout < charge->getAuteur();


    cout <<"-------- 0 : " <<charge->getEtatsPossibles()->getListe()[0].getIndice() <<endl;
    //cout << " ____ : " << charge->getEnsemble()->getListe()[0].getIndice() <<endl;


    cout <<"-------- 1 : " <<charge->getEtatsPossibles()->getListe()[1].getIndice() <<endl;

    return charge;

}
