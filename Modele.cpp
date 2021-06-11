#include "Modele.h"
#include <iostream>
// #include "outil.h"
#include "pugixml.hpp"

using namespace std;
using namespace pugi;

Modele::Modele()
{
    //this->typeVoisinnage =
    this->typeVoisinnage = new V_ChoixUtilisateur();
    this->etatsPossibles = new EnsembleEtats(10);
    this->fonctionTrans = new FonctionTransition;
}
string *generation_regles_Brians_Brain(const unsigned int nb_voisins)
{
    string tab[100]; //etat depart_mort_refractaire_excite _etatarrivee
    string nouvelle_regle;
    int l = 0;
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            for (size_t k = 0; k < 10; k++)
            {
                if (i + k + j == nb_voisins)
                {
                    nouvelle_regle = "2" + to_string(i) + to_string(j) + to_string(k) + "1";
                    tab[l] = nouvelle_regle;
                    l++;
                    nouvelle_regle = "1" + to_string(i) + to_string(j) + to_string(k) + "0";
                    tab[l] = nouvelle_regle;
                    if (k == 2)
                    {
                        nouvelle_regle = "0" + to_string(i) + to_string(j) + "2" + "2";
                        tab[l] = nouvelle_regle;
                        l++;
                    }
                }
            }
        }
        return tab;
    }

    return tab;
}
string *generation_regles_Life_game(const unsigned int nb_voisins)
{
    string tab[nb_voisins]; //une cellule morte possédant exactement trois voisines vivantes devient vivante (elle naît)
                            // une cellule vivante possédant deux voisines vivantes le reste,sinon elle meurt.

    tab[0] = "0" + to_string(nb_voisins - 3) + "3" + "1";
    string regle_2 = to_string(nb_voisins - 2) + "2";
    string regle_3 = to_string(nb_voisins - 3) + "3";

    string nouvelle_regle;
    int nb_mort;
    int nb_vivant;
    int i = 1;
    int j = 0;
    while (j <= nb_voisins)
    {
        nb_mort = j;
        nb_vivant = nb_voisins - j;
        nouvelle_regle = to_string(j) + to_string(nb_vivant);
        if (!((nouvelle_regle == regle_2) || (nouvelle_regle == regle_3)))
        {
            tab[i] = "1" + nouvelle_regle + "0";
            i++;
        }
        j++;
    }
    return tab;
}
    // ça arrive
    char FonctionTransition::comparaison_voisinnage(string voisins, string * trans, char cel, unsigned int limit, int nb_Etat)
    {
        // pour un voisinnage donné on va vérifier si ce voisinnage est dans
        // le tableau de fonction transition si oui on va renvoyer un caractère qui
        // va correspondre à l'état de la cellule à la génération t+1
        unsigned int i = 0;
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

    char FonctionTransitionIntention::comparaison_voisinnage(string voisins, string * trans, char cel, unsigned int limit, int nb_Etat)
    {
        auto tab = new int[nb_Etat]; //initialisation du tableau
        for (int i = 0; i < nb_Etat; i++)
        {
            tab[i] = 0;
        }

        for (int i = 0; i < voisins.length(); i++)
        {
            tab[voisins[i] - '0']++; //pour chaque cellule du voisinnage on va ajouter une occurence à la case du tableau correspond à son état
        }

        string tab_de_inten;
        char c;
        for (int i = 0; i < nb_Etat; i++)
        { //ici on crée la chaîne de caractère que l'on va comparer avec les règles de transition
            c = tab[i] + '0';
            //cout<<tab[i]<<"=tab[i]\n";
            //cout<<c<<"=c\n";
            tab_de_inten.push_back(c);
        }

        int test = 0;
        int i = 0;
        string st;

        while (i < limit && (trans[i][0] == cel))
        {
            st = trans[i].substr(1, trans[i].length() - 2); //ici on prélève la partie de la règle qui nous intéresse
            cout << st << "=st\n";
            cout << tab_de_inten << "=tab_de_inten\n";
            test = st.compare(tab_de_inten);
            if (test == 0)
            {
                size_t j = (trans[i].length() - 1);
                return trans[i][j];
            }
            i++;
        }
        return cel;
    };

    int char_to_int(char c)
    {
        int b = 0;
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
        Etat *e = new Etat;
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
                etatDest = fonctionTrans->comparaison_voisinnage(dep.getVoisinage(i, j, *typeVoisinnage), fonctionTrans->tableau + p, *etatDepart, fonctionTrans->taille - p, etatsPossibles->getNombreEtats());
                //cout<<"etat dest : "<<char_to_int(etatDest)<<"\n";
                e = (*etatsPossibles)[char_to_int(etatDest)]; // vis-à-vis de la surcharge de l'opérateur [] à revoir
                dest.setEtatCellule(i, j, e);
                p = 0;
            }
        }
    }
    /*
Modele creerModele()
{
    string titre; //key

    FonctionTransition *fonctionTrans;
    string description;
    string auteur;
    int nb_etat;
    unsigned int anneeCreation;
    std::cout << "Quel est le titre de votre modèle ? ";
    std::cin >> titre;
    std::cout << "Quel est la description de votre modèle ? ";
    std::cin >> description;
    std::cout << "Qui est l'auteur de votre modèle ? ";
    std::cin >> auteur;
    std::cout << "Quel est la l'anne de creation de votre modèle ? ";
    std::cin >> anneeCreation;
    std::cout << "De combien d'états est composé votre modèle ?";
    std::cin >> nb_etat;
    EnsembleEtats ensembleEtat(nb_etat);
    for (int i = 0; i < nb_etat; i++)
    {
        string s;
        int j;
        std::cout << "Quelle est le label du"<<i<< " ème état";
        std::cin >> s;
        ensembleEtat.getListe()[i].setlabel(s);
        std::cout << "Quelle est l'indice du"<< i<< " ème état";
        std::cin >> j;
        ensembleEtat.getListe()[i].setIndice(j);
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
    case 1:                                           // si voisinnage de VonNeumann
        static Voisinage typeVoisinnage_VonNeuman(4); // type Static car doit exister en dehors du switch
        static Case *ensemble_de_cases_VonNeuman;     // type Static car doit exister en dehors du switch
        ensemble_de_cases_VonNeuman[0].setL(0);       //Pour l'Est de la case
        ensemble_de_cases_VonNeuman[0].setC(1);
        ensemble_de_cases_VonNeuman[1].setL(-1); // Pour le Sud de la case
        ensemble_de_cases_VonNeuman[1].setC(0);
        ensemble_de_cases_VonNeuman[2].setL(0); // Pour l'Ouest de la case
        ensemble_de_cases_VonNeuman[2].setC(-1);
        ensemble_de_cases_VonNeuman[3].setL(1); // Pour le Nord de la case
        ensemble_de_cases_VonNeuman[3].setL(0);
        break;

    case 2:
        static Voisinage typeVoisinnage_Moore(8); // type Static car doit exister en dehors du switch
        static Case *ensemble_de_cases_Moore;     // type Static car doit exister en dehors du switch
        ensemble_de_cases_Moore[0].setL(0);       //Pour l'Est de la case
        ensemble_de_cases_Moore[0].setC(1);
        ensemble_de_cases_Moore[1].setL(-1); //Pour le Sud-est de la case
        ensemble_de_cases_Moore[1].setC(1);
        ensemble_de_cases_Moore[2].setL(-1); // Pour le Sud de la case
        ensemble_de_cases_Moore[2].setC(0);
        ensemble_de_cases_Moore[3].setL(-1); // Pour le Sud-ouest de la case
        ensemble_de_cases_Moore[3].setC(-1);
        ensemble_de_cases_Moore[4].setL(0); // Pour l'Ouest de la case
        ensemble_de_cases_Moore[4].setC(-1);
        ensemble_de_cases_Moore[5].setL(1); // Pour le Nord-ouest de la case
        ensemble_de_cases_Moore[5].setC(-1);
        ensemble_de_cases_Moore[6].setL(1); // Pour le Nord de la case
        ensemble_de_cases_Moore[6].setL(0);
        ensemble_de_cases_Moore[7].setL(1); // Pour le Nord-est de la case
        ensemble_de_cases_Moore[7].setC(1);
        break;

    case 3:
        break;
    case 4:
        break;
    case 5:
        std::cout << "Quel est le nombre de voisin ?";
        int nb_voisins;
        static Voisinage typeVoisinnage_arbitraire(nb_voisins);
        static Case *ensemble_de_cases_arbitarire;
        int l;
        int c;
        for (size_t i = 0; i < 4; i++)
        {
            std::cout << "Quelle est la ligne du "<< i<< " ème voisin relativement à la position de la case ?";
            std::cin >> l;
            ensemble_de_cases_arbitarire[i].setL(l);
            std::cout << "Quelle est la ligne du "<< i<< " ème voisin relativement à la position de la case ?";
            std::cin >> c;
            ensemble_de_cases_arbitarire[i].setL(c);
        }
        break;

        // typeVoisinnage->setensemble_case break;

    default:
        break;
    }
};
*/

    void Modele::sauvegardeM()
    {
        //Création du doc
        xml_document doc;
        string xmlFilePath = "../LO21---Printemps-2021---Projet-Cellulut/Modeles/";
        xmlFilePath += this->getTitre();
        xmlFilePath += ".xml";

        //Il faut vérifier qu'aucun modèle avec ce titre n'existe :

        xml_parse_result result = doc.load_file(xmlFilePath.c_str(), parse_default | parse_declaration);
        if (result)
        {
            cout << "Il existe deja un modele avec ce titre";
            return;
        }

        auto declarationNode = doc.append_child(pugi::node_declaration);
        //En tête
        declarationNode.append_attribute("version") = "1.0";
        //Déclaration balise et attribut
        xml_node modele = doc.append_child("Modele");
        xml_node titre = modele.append_child("titre");
        titre.append_attribute("name") = this->getTitre().c_str();

        xml_node Description = modele.append_child("Description");
        Description.append_attribute("name") = this->getDescription().c_str();

        xml_node Auteur = modele.append_child("Auteur");
        Auteur.append_attribute("name") = this->getAuteur().c_str();

        xml_node annee = modele.append_child("AnneeCreation");
        annee.append_attribute("name") = this->getAnnee();

        //Les attributs d'un état
        xml_node etats = modele.append_child("Etats");
        xml_node NbrEtat = etats.append_child("NombreEtat");
        int nbr = this->getEnsemble()->getNombreEtats();
        NbrEtat.append_attribute("name") = nbr;
        //Faire un while sur le nbr d'état
        Etat *laListe = this->getEnsemble()->getListe();
        for (int i = 0; i < nbr; i++)
        {
            xml_node etat = etats.append_child("Etat");
            etat.append_attribute("Label") = laListe[i].getLabel().c_str();
            etat.append_attribute("Couleur") = laListe[i].getCouleur().c_str();
            etat.append_attribute("Indice") = laListe[i].getIndice();
        }

        //Gestion du voisinage
        xml_node voisinage = modele.append_child("Voisinage");
        xml_node nom = voisinage.append_child("Nom");
        Voisinage *voi = this->getVoisin();
        nom.append_attribute("name") = voi->getTypeVoisi().c_str();

        //Quand le voisinage sera terminé
        /*  xml_node rayon = voisinage.append_child("Rayon");
    rayon.append_attribute("name")="1";*/
        //Gestion des éléments, faire un while aussi

        xml_node element = voisinage.append_child("Element");
        int nbrCase = this->getVoisin()->getNbCelluleVoisi();
        Case *listeCase = this->getVoisin()->getTableau();
        for (int i = 0; i < nbrCase; i++)
        {
            xml_node caseCoord = element.append_child("Case");
            caseCoord.append_attribute("X") = listeCase[i].getL();
            caseCoord.append_attribute("Y") = listeCase[i].getC();
        }

        //gestion des règles

        xml_node typeF = modele.append_child("TypeFonctionTransition");
        typeF.append_attribute("name") = getTypeFonction().c_str();
        xml_node liste = modele.append_child("ListeRegle");
        const unsigned int tailleR = this->getFonction()->getTaille();
        string *regles = this->getFonction()->getTableau();
        for (unsigned int i = 0; i < tailleR; i++)
        {
            xml_node regle = liste.append_child("Regle");
            regle.append_attribute("name") = regles[i].c_str();
        }
        xml_node configs = modele.append_child("ListeConfig");
        configs.append_attribute("nombre") = 0;

        bool saveSuccess = doc.save_file(xmlFilePath.c_str(), PUGIXML_TEXT("   "));
        cout << saveSuccess;
    }

