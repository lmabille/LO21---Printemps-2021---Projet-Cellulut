/**
 * @file chargerModele.cpp
 * @author Thomas Guegan (you@domain.com)
 * @brief chargement du modèle depuis XML
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "chargerModele.h"
#include <iostream>
#include "pugixml.hpp"
#include "Modele.h"

using namespace pugi;
using namespace std;



/**
 * @brief fonction permettant de charger un modèle à partir d'un fichier
 *
 * @param[in] adresse du fichier correspondant au modèle ( relative ou absolue )
 * @return retourne le modèle contenant les informations du fichier
 */

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


        string tmp = it->name();
        string val;

        for (xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait) {

            val = ait->value(); // On récupère la valeur de l'attribut de la balise pour les informations auteur, titre , desc, annee
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
            //cout <<endl;



            Etat * liste = new Etat[15] ();
            int n=0;

            xml_node test = tools.child("Etats"); // on rentre dans la balise <Etats> du xml



            for (xml_node_iterator it2 = test.begin(); it2 != test.end(); ++it2) { //Pour chaque balise à l'interieur de <Etats>
                string* lst_attri ;



                string nom = it2->name();
                int indice =0;




                int compteur =0;
                for (xml_attribute_iterator cpt = it2->attributes_begin(); cpt != it2->attributes_end(); ++cpt) {

                    if (compteur !=0) // si on est pas dans la première balise ( balise du nombre d etats )
                    {

                        compteur =0;
                    }
                    else{ // si on est dans la balise du nombre d etats on recupere la valeur
                        val = cpt->value();
                        compteur ++;
                    }

                }

                if (nom == "NombreEtat") {

                    charge->initEnsemble(stoi(val)); // on instancie un ensemble de la bonne taille dans le modèle
                }
                if (nom == "Etat") {

                    string label;
                    string couleur;

                    int v_cpt = 0;
                    for (xml_attribute_iterator cpt = it2->attributes_begin(); cpt != it2->attributes_end(); ++cpt) { // Pour chaque attribut de la balise <Etat>
                        val = cpt->value();
                        if ( v_cpt == 0){
                            label = cpt->value(); // premier attribut : le label

                            v_cpt ++;
                        }

                        else if ( v_cpt == 1) {
                            couleur = cpt->value(); // deuxieme attribut  : la couleur
                            v_cpt ++;
                        }

                        else if ( v_cpt == 2  ) {


                            indice = stoi(cpt->value()); // 3eme attribut l'indice de l'état

                            v_cpt ++;
                        }



                    }

                    //On enregistre les informations recuperer
                    liste[n].setlabel(label);
                    liste[n].setIndice(indice);
                    liste[n].setCouleur(couleur);


                    n++;
                }

            }


            charge->getEnsemble()->setListe(liste); // on enregistre la liste d'etat dans le modele



        }

        if (tmp == "Voisinage") { // si on est dans la balise voisinage


            xml_node test = tools.child("Voisinage");
            string name = test.begin()->attributes_begin()->value(); // on recupere le nom du voisinage



            test = test.child("Element"); // on rentre dans la balise <Element> contenant la liste de case


            int taille = 15;
            Case* liste_voisin = new Case[taille](); // on créer un tableau de case de taille 15

            int nbVoisin =0;
            for (xml_node_iterator it2 = test.begin(); it2 != test.end() ; ++it2) { // on parcour les balises dans la balise <Element>


                string nom = it2->name();

                int x_y_test = 0;
                int x = 0;
                int y = 0;

                for (xml_attribute_iterator cpt = it2->attributes_begin(); cpt != it2->attributes_end(); ++cpt) {// on parcour les attributs de la balise <Case>



                    val = cpt->value();
                    if (x_y_test == 0){  //Si on est en train de lire la valeur de x
                        x = stoi(val);
                        x_y_test ++;
                    }
                    if (x_y_test == 1) { //Si on est en train de lire la valeur de y
                        y = stoi(val);

                    }


                }



                if (nbVoisin == taille) { // si on arrive le tableau de case initialiser plus tot est plein on en créer un nouveau de taille supérieur

                    Case* tempo = new Case[taille+15]();
                    for (int j =0; j< taille ; j++ ) {
                        tempo[j] = liste_voisin[j]; // on recopie chaque case de l'ancien tableau dans le nouveau
                    }
                    taille = taille + 15;
                    delete [] liste_voisin; // on supprime l'ancien tableau
                    liste_voisin = tempo;

                }
                liste_voisin[nbVoisin] = Case(x,y);  // on attribut à la bonne case du tableau une Case de valeur x et y

                nbVoisin++;




            }


            charge->getVoisin()->setensemble_case(liste_voisin); // on enregistre la liste de voisin dans le modèle
            charge->getVoisin()->setNbCellule(nbVoisin); // on enregistre le nombre de voisin


        }

        if (tmp == "TypeFonctionTransition") {

            charge->setTypef(it->attributes_begin()->value()); // on enregistre le type de fonction de transition (intension/ extension)

        }


        if (tmp == "ListeRegle") { // si on est au niveau de la balise ListeRegle


            xml_node test = tools.child("ListeRegle"); // on rentre dans la balise
            string name = test.begin()->attributes_begin()->value();




            int taille = 15;
            string* liste_regle = new string[15](); // on creer le tableau de string pour enregistrer les regles

            int nbRegles =0;
            for (xml_node_iterator it2 = test.begin(); it2 != test.end() ; ++it2) { // on parcours toutes les balises de regle


                string nom = it2->name();



                for (xml_attribute_iterator cpt = it2->attributes_begin(); cpt != it2->attributes_end(); ++cpt) { // on recupere la valeur de l'attribut (la regle)

                    val = cpt->value();

                }



                if (nbRegles == taille) { // si le tableau est plein on en créer un de taille supérieur
                    string* tempo = new string[taille*2]();
                    for (int j =0; j< taille ; j++ ) {
                        tempo[j] = liste_regle[j]; //on recopie les elements
                    }
                    taille = taille *2;
                    delete [] liste_regle; // on supprime l'ancien
                    liste_regle = tempo;

                }

                liste_regle[nbRegles] = val; // on ajoute la regle

                nbRegles++;



            }


            FonctionTransition * fct;
            if (charge->getTypeFonction() == "extension") { // en fonction du type de fonction de transition on instancie la classe correspondante
                fct = new FonctionTransition(liste_regle,nbRegles);
            }
            else {
                fct = new FonctionTransitionIntention(liste_regle,nbRegles);
            }



            charge->setFonction(fct);



        }

    }



    return charge;

}
