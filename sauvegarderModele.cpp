#include "sauvegarderModele.h"
#include <iostream>
#include "pugixml.hpp"

using namespace std;

using namespace pugi;
void Modele::sauvegardeM(Modele M){
 //Création du doc
    xml_document doc;
    auto declarationNode = doc.append_child(node_declaration);
    //En tête
    declarationNode.append_attribute("version")="1.0";
    //Déclaration balise et attribut
    xml_node modele = doc.append_child("Modele");
    xml_node titre = modele.append_child("titre");
    titre.append_attribute("name")=M.getTitre();

    xml_node Description = modele.append_child("Description");
    Description.append_attribute("name")="Le jeu de la vie";

    xml_node Auteur = modele.append_child("Auteur");
    Auteur.append_attribute("name")="M.Dupont";

    xml_node annee = modele.append_child("AnneeCreation");
    annee.append_attribute("name")="2021";

    //Les attributs d'un état
    xml_node etat = modele.append_child("Etat");
    xml_node NbrEtat = etat.append_child("NombreEtat");
    NbrEtat.append_attribute("name")="2";
    //Faire un while sur le nbr d'état
    xml_node label = etat.append_child("Label");
    label.append_attribute("name")="rouge";
    label = etat.append_child("Label");
    label.append_attribute("name")="noir";

    //Gestion du voisinage
    xml_node voisinage = modele.append_child("Voisinage");
    xml_node nom = voisinage.append_child("Nom");
    nom.append_attribute("name")="VonNeumann";

    //Faire la vérification, soit rayon/soit élément
    xml_node rayon = voisinage.append_child("Rayon");
    rayon.append_attribute("name")="1";
    //Gestion des éléments, faire un while aussi
    xml_node element = voisinage.append_child("Element");
    xml_node caseCoord = element.append_child("Case");
    caseCoord.append_attribute("X")="1";
    caseCoord.append_attribute("Y")="-1";

    //Gestion des règles
    xml_node liste = modele.append_child("ListeRegle");
    xml_node regle = liste.append_child("Regle");
    regle.append_attribute("name")="100011";
    regle = liste.append_child("Regle");
    regle.append_attribute("name")="001001";



    //Sauvegarde du doc
    bool saveSuccess = doc.save_file("demo.xml", PUGIXML_TEXT("   "));
    cout<<saveSuccess;
}
