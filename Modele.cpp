#include "Modele.h"
#include <iostream>
// #include "outil.h"

using namespace std;

// ça arrive
char comparaison_voisinnage(string voisins, string *trans, char cel, unsigned int limit)
{
    // pour un voisinnage donné on va vérifier si ce voisinnage est dans
    // le tableau de fonction transition si oui on va renvoyer un caractère qui
    // va correspondre à l'état de la cellule à la génération t+1
    int i = 0;
    int test = 0;
    string st;
    //cout << "compa_vois"
    //     << "\n";
    while (i < limit && (trans[i][0] == cel))
    {
        //cout << "passeboucle"
        //     << "\n\n";
        st = trans[i].substr(1, trans[i].length() - 2);
        st.append(st);
        //cout << voisins << "\n";
        test = st.find(voisins);
        if (test != -1)
        {
            size_t j = (trans[i].length() - 1);
            return trans[i][j];
        }
        i++;
    }
    return cel;
}

int char_to_int(char c)
{
    int b=0;
    char p = c;
    b = p - '0';
    return b;
}

void Modele::appliquerTransition(const Configuration &dep, Configuration &dest) const
/* Pour chaque cellule de la configuration de départ, récupère ses voisins, récupère son état, et détermine son état d'arrivée qu'elle place dans la confifuration de destinationn*/
{
    if (dep.getReseauLignes() != dest.getReseauLignes() || dep.getReseauColonnes() != dest.getReseauColonnes())
        dest = dep;
    char *etatDepart = new char;
    char etatDest;
    Etat * e = new Etat;
    unsigned int p = 0;

    for (int i = 0; i < dep.getReseauLignes(); i++)
    {
        for (int j = 0; j < dep.getReseauColonnes(); j++)
        {
            while (p < fonctionTrans->taille && ((int)((fonctionTrans->tableau)[p][0]) != ('0' + dep.getEtatCellule(i, j).getIndice())))
            {
                p++;
            };
            sprintf(etatDepart, "%d", dep.getEtatCellule(i, j).getIndice());
            //cout << "voisinnage : "<<dep.getVoisinage(i, j, *typeVoisinnage) << "\n";
            etatDest = comparaison_voisinnage(dep.getVoisinage(i, j, *typeVoisinnage), fonctionTrans->tableau + p, *etatDepart, fonctionTrans->taille - p);
            //cout<<"etat dest : "<<char_to_int(etatDest)<<"\n";
            e = (*etatsPossibles)[char_to_int(etatDest)]; // vis-à-vis de la surcharge de l'opérateur [] à revoir
            dest.setEtatCellule(i, j, e);
            p=0;
        }
    }
}

void Modele::creerModele()
{
    string titre; //key
    Etat **ensembleEtat;
    string *regles;
    Voisinage *typeVoisinnage;
    FonctionTransition *fonctionTrans;
    string description;
    string auteur;
    string label;
    unsigned int nb_etat;
    unsigned int anneeCreation;
    std::cout << "Quel est le titre de votre modèle ?";
    std::cin >> titre;
    std::cout << "De combien d'état est composé votre modèle ?";
    std::cin >> nb_etat;
    for (size_t i = 0; i < nb_etat; i++)
    {
        printf("Veuillez donner le label de l'état n° %d", i);
        std::cin >> label;
        ensembleEtat[0]->setIndice(i);
        ensembleEtat[0]->setlabel(label);
    }
    std::cout << "Quel type de voisinage souhaitez-vous ? \n \
    1 - Voisinnage de von Neumann \n \
    2 - Voisinnage de von Neumann généralisé avec un rayon r \n \
    3 - Voisinnage de Moore \n \
    4 - Voisinnage de Moore généralisé avec un rayon r \n \
    5 - Voisinnage arbitraire \n \
    Veuillez choisir un chiffre";
    unsigned int choix;
    std::cin >> choix;
    switch (choix)
    {
    case 1:
        typeVoisinnage->setNbCellule(4);
        // typeVoisinnage->setensemble_case break;

    default:
        break;
    }
};


void Modele::sauvegardeM(){
 //Création du doc
    pugi::xml_document doc;
    string xmlFilePath = "Modeles/";
    xmlFilePath += this->getTitre();
    xmlFilePath += ".xml";
    auto declarationNode = doc.append_child(pugi::node_declaration);
    //En tête
    declarationNode.append_attribute("version")="1.0";
    //Déclaration balise et attribut
    pugi::xml_node modele = doc.append_child("Modele");
    pugi::xml_node titre = modele.append_child("titre");
    titre.append_attribute("name")=this->getTitre().c_str();

    pugi::xml_node Description = modele.append_child("Description");
    Description.append_attribute("name")=this->getDescription().c_str();

    pugi::xml_node Auteur = modele.append_child("Auteur");
    Auteur.append_attribute("name")=this->getAuteur().c_str();

    pugi::xml_node annee = modele.append_child("AnneeCreation");
    annee.append_attribute("name")=this->getAnnee();

    //Les attributs d'un état
    pugi::xml_node etat = modele.append_child("Etat");
    pugi::xml_node NbrEtat = etat.append_child("NombreEtat");
    int nbr =this->getEnsemble()->getNombreEtats();
    NbrEtat.append_attribute("name")=nbr;
    //Faire un while sur le nbr d'état
    Etat *laListe = this->getEnsemble()->getListe();
    for(int i=0; i<nbr; i++){
    pugi::xml_node label = etat.append_child("Label");
    label.append_attribute("name")=laListe[i].getLabel().c_str();
    }


    //Gestion du voisinage
    pugi::xml_node voisinage = modele.append_child("Voisinage");
    pugi::xml_node nom = voisinage.append_child("Nom");
    Voisinage * voi = this->getVoisin();
    nom.append_attribute("name")=voi->getTypeVoisi().c_str();

    //Quand le voisinage sera terminé
  /*  xml_node rayon = voisinage.append_child("Rayon");
    rayon.append_attribute("name")="1";*/
    //Gestion des éléments, faire un while aussi
    pugi::xml_node element = voisinage.append_child("Element");
    int nbrCase = this->getVoisin()->getNbCelluleVoisi();
    Case * listeCase = this->getVoisin()->getTableau();
    for(int i=0; i<nbrCase; i++){
        pugi::xml_node caseCoord = element.append_child("Case");
        caseCoord.append_attribute("X")=listeCase[i].getL();
        caseCoord.append_attribute("Y")=listeCase[i].getC();
    }
    //Gestion des règles
    pugi::xml_node liste = modele.append_child("ListeRegle");
    pugi::xml_node regle = liste.append_child("Regle");
    const unsigned int tailleR = this->getFonction()->getTaille();
    string *regles=this->getFonction()->getTableau();
    for(int i=0; i<tailleR; i++)regle.append_attribute("name")=regles[i].c_str();




    //Sauvegarde du doc this->getTitre().c_str()
    bool saveSuccess = doc.save_file(xmlFilePath.c_str(), PUGIXML_TEXT("   "));
    cout<<saveSuccess;
}
