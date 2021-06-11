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
    //Rappel des règles :
    //les cellules excitées deviennent toujours réfractaires au pas de temps suivant (R1) ;
    //les cellules réfractaires reviennent toujours au repos (=mort) au pas de temps suivant (R2) ;
    //une cellule au repos devient excitée au pas de temps suivant si elle a exactement 2 cellules voisines excitées (R3)

    // 0 : mort | 1 : refractaire | 2 : excite
    //etat depart| nb_voisins_mort(i) | nb_voisins_refractaire(j) | nb_voisins_excite(k) | etat arrivee

    // EXEMPLE : 12423 --> execution de R1 avec nb_voisin = 8 (2+4+2)

    //principe algo : on cherche à obtenir un triplet | nb_mort | nb_voisins_refractaire | nb_voisins_excite | dont la somme de chacun est égale au nombre de voisins

    string tab[100];
    int l = 0;

    for (size_t i = 0; i < 10; i++) //nb_mort
    {
        for (size_t j = 0; j < 10; j++) // nb_voisins_mort
        {
            for (size_t k = 0; k < 10; k++) //nb_voisins_excite
            {
                if (i + k + j == nb_voisins) //si le triplet = nb_voisins
                {
                    tab[l] = "2" + to_string(i) + to_string(j) + to_string(k) + "1"; //Ajout de R1 (pas de condition sur les voisins)
                    l++;
                    tab[l] = "1" + to_string(i) + to_string(j) + to_string(k) + "0"; //Ajout de R2 (pas de condition sur les voisins)
                    l++;
                    if (k == 2) // si nombre de voisins excités est de 3
                    {
                        tab[l] = "0" + to_string(i) + to_string(j) + "2" + "2"; //Ajout de R3
                        l++;
                    }
                }
            }
        }
    }

    return tab;
}
string *generation_regles_Life_game(const unsigned int nb_voisins)
{
    //Rappel des règles :
    //Une cellule morte possédant exactement trois voisines vivantes devient vivante (R1)
    //Une cellule ne possédant PAS deux voisines vivantes devient morte (R2)
    //Une cellule ne possédant PAS trois voisines vivantes devient morte (R3)

    // 0 : mort | 1 : vivante
    //etat depart| nb_voisins_mort(i) | nb_voisins_vivant | etat arrivee

    string tab[nb_voisins];

    tab[0] = "0" + to_string(nb_voisins - 3) + "3" + "1"; //Ajout de R1, le nombre de voisin vivant est forcément égale à nb_voisins - 3

    //Pour R2, et R3 on crée deux cas :
    string regle_2 = to_string(nb_voisins - 2) + "2"; //un doublet avec nb_voisins_mort est de 2
    string regle_3 = to_string(nb_voisins - 3) + "3"; //un doublet avec nb_voisins_mort est de 3
    //On
    string nouvelle_regle;
    int i = 1; //index du tableau débute à 1 car on a déjà ajouté une régle
    int j = 0; // j représente le nombre de voisins mort
    while (j <= nb_voisins)
    {
        nouvelle_regle = to_string(j) + to_string(nb_voisins - j);         //on tous les doublets donc la somme = nb_voisins
        if (!((nouvelle_regle == regle_2) || (nouvelle_regle == regle_3))) // si, dans ce doublet, l'un est égale à une des deux règle du dessus, alors on ne rentre pas dans le if
        {
            tab[i] = "1" + nouvelle_regle + "0"; //ajout de la règle si il n'y a ni 2 ni 3 voisins vivants
            i++;
        }
        j++;
    }
    return tab;
}

string *generation_regles_Griffeath(const unsigned int nb_voisins)
{
    //Rappel des règles :
    // une cellule passe de l’état i à i + 1 (modulo 4) dès que i + 1 (modulo 4) est présent dans au moins 3 cellules voisines.

    //etat_depart | 0 (jaune, i) |  1 (orange clair, j) | 2 (orange foncé, k) |  3 (rouge, l) | etat_arrivee

    //EXEMPLE :
    //  013401 --> passe de l'etat 0 à 1 car il y a 3 voisins dans l'état 1 (8 voisins)
    //  004401 --> passe de l'etat 0 à 1 car il y a 4 voisins dans l'état 1 (8 voisins)
    //  12242 --> passe de l'etat 1 à 2  car il y a 4 voisins dans l'état 2 (8 voisins)

    //principe algo : on cherche à obtenir un quadruplet | nb_voisins_0 | nb_voisins_1 | nb_voisins_2 | nb_voisins_3 dont la somme de chacun est égale au nombre de voisins

    string tab[500];
    int m = 0;
    for (size_t i = 0; i < 10; i++) // nb_voisins à 0 (jaune)
    {
        for (size_t j = 0; j < 10; j++) // nb_voisins à 1 (orange clair)
        {
            for (size_t k = 0; k < 10; k++) //  nb_voiins à 2 (orange foncé)
            {
                for (size_t l = 0; l < 10; l++) // nb_voisins à 3 (rouge)
                {
                    if ((i + j + k + l) == nb_voisins) // Si la somme du quadruplet donne le nombre de voisins
                    {
                        if (j >= 3) // si etat 1 superieur ou egale à 3, alors on passe de l'etat 0 à 1
                        {
                            tab[m] = "0" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "1";
                            m++;
                        }
                        if (k >= 3) // si etat 2 superieur ou egale à 3, alors on passe de l'etat 1 à 2
                        {
                            tab[m] = "1" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "2";
                            m++;
                        }
                        if (l >= 3) // si etat 3 superieur ou egale à 3, alors on passe de l'etat 2 à 3
                        {
                            tab[m] = "2" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "3";
                            m++;
                        }
                        if (i >= 3) // si etat 0 superieur ou egale à 3, alors on passe de l'etat 3 à 0 (car modulo)
                        {
                            tab[m] = "3" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "0";
                            m++;
                        }
                    }
                }
            }
        }
    }
    return tab;
}

string *generation_regles_Wireworld(const unsigned int nb_voisins)
{
    //Rappel règles:

    // Une tête d'électron devient une queue d'électron (R1)
    // Une queue d'électron devient un conducteur (R2)
    // Un conducteur devient une tête d'électron si une ou deux des cellules voisines sont des têtes d'électron (R3)

    // etat_depart | nb_voisins_vide(i) |  nb_voisins_conducteur(j) | nb_voisins_electron_tete(k) |  nb_voisins_electron_queue(l) | etat_arrivee

    //0 = Vide
    //1 = conducteur
    //2 = tete electron
    //3 = Electron queue

    string tab[500];
    int m = 0;
    for (size_t i = 0; i < 10; i++) //nb_voisins vide
    {
        for (size_t j = 0; j < 10; j++) //nb_voisins conducteur
        {
            for (size_t k = 0; k < 10; k++) //nb_voisins  electron tete
            {
                for (size_t l = 0; l < 10; l++) // nb_voisins electron queue
                {
                    if ((i + j + k + l) == nb_voisins) //Si la somme du quadruplet donne le nombre de voisins
                    {
                        tab[m] = "2" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "3"; //Ajout de R1 (pas de condition sur voisinage)
                        m++;
                        tab[m] = "3" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "1"; //Ajout de R2 (pas de condition sur voisinage)
                        m++;
                        if ((k == 1) || (k == 2)) // si nb_voisins electron tête est de 1 ou 2
                        {
                            tab[m] = "1" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "2"; // alors passage de l'état conducteur à tête electron
                            m++;
                        }
                    }
                }
            }
        }
    }
    return tab;
}
// ça arrive
char FonctionTransition::comparaison_voisinnage(string voisins, string *trans, char cel, unsigned int limit, int nb_Etat)
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

char FonctionTransitionIntention::comparaison_voisinnage(string voisins, string *trans, char cel, unsigned int limit, int nb_Etat)
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
