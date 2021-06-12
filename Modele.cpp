#include "Modele.h"
#include <iostream>
// #include "outil.h"
#include "pugixml.hpp"

using namespace std;
using namespace pugi;

char to_alphabet(int n)
{
    int res = n;
    if (n > 9)
    {
        res = n + 'A' - 10;
        return res;
    }
    return '0' + res;
}
Modele::Modele()
{
    //this->typeVoisinnage =
    this->typeVoisinnage = new V_ChoixUtilisateur();
    this->etatsPossibles = new EnsembleEtats(10);
    this->fonctionTrans = new FonctionTransition;
}
string *generation_regles_Brians_Brain(const unsigned int nb_voisins, int &l)
{
    //Rappel des règles :
    //les cellules excitées deviennent toujours réfractaires au pas de temps suivant (R1) ;
    //les cellules réfractaires reviennent toujours au repos (=mort) au pas de temps suivant (R2) ;
    //une cellule au repos devient excitée au pas de temps suivant si elle a exactement 2 cellules voisines excitées (R3)

    // 0 : mort | 1 : refractaire | 2 : excite
    //etat depart| nb_voisins_mort(i) | nb_voisins_refractaire(j) | nb_voisins_excite(k) | etat arrivee

    // EXEMPLE : 12423 --> execution de R1 avec nb_voisin = 8 (2+4+2)

    //principe algo : on cherche à obtenir un triplet | nb_mort | nb_voisins_refractaire | nb_voisins_excite | dont la somme de chacun est égale au nombre de voisins

    string *tab;
    tab = new string[100]; //etat depart_mort_refractaire_excite _etatarrivee
    //string tab[100];
    string nouvelle_regle;
    l = 0; //indexe du tableau
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            for (size_t k = 0; k < 10; k++)
            {
                if (i + k + j == nb_voisins)
                {
                    //nouvelle_regle = "2" + to_string(i) + to_string(j) + to_string(k) + "1";
                    nouvelle_regle.push_back('2');
                    nouvelle_regle.push_back(to_alphabet(i));
                    nouvelle_regle.push_back(to_alphabet(j));
                    nouvelle_regle.push_back(to_alphabet(k));
                    nouvelle_regle.push_back('1');
                    tab[l] = nouvelle_regle;
                    l++;
                    nouvelle_regle = "";
                    //nouvelle_regle = "1" + to_string(i) + to_string(j) + to_string(k) + "0";
                    nouvelle_regle.push_back('1');
                    nouvelle_regle.push_back(to_alphabet(i));
                    nouvelle_regle.push_back(to_alphabet(j));
                    nouvelle_regle.push_back(to_alphabet(k));
                    nouvelle_regle.push_back('0');
                    tab[l] = nouvelle_regle;
                    l++;
                    nouvelle_regle = "";
                    if (k == 2)
                    {
                        //nouvelle_regle = "0" + to_string(i) + to_string(j) + "2" + "2";
                        nouvelle_regle.push_back('0');
                        nouvelle_regle.push_back(to_alphabet(i));
                        nouvelle_regle.push_back(to_alphabet(j));
                        nouvelle_regle.push_back('2');
                        nouvelle_regle.push_back('2');
                        tab[l] = nouvelle_regle;
                        nouvelle_regle = "";
                        l++;
                    }
                }
            }
        }
    }
    return tab;
};

string *generation_regles_Life_game(const unsigned int nb_voisins, int &l)
{
    //Rappel des règles :
    //Une cellule morte possédant exactement trois voisines vivantes devient vivante (R1)
    //Une cellule ne possédant PAS deux voisines vivantes devient morte (R2)
    //Une cellule ne possédant PAS trois voisines vivantes devient morte (R3)

    // 0 : mort | 1 : vivante
    //etat depart| nb_voisins_mort(i) | nb_voisins_vivant | etat arrivee

    auto tab = new string[100];
    string regle;
    l = nb_voisins ;
    regle.push_back('0');
    regle.push_back(to_alphabet(nb_voisins - 3));
    regle.push_back('3');
    regle.push_back('1');
    tab[0] = regle;
    // tab[0] = "0" + to_alphabet(nb_voisins - 2) + "3" + "1"; //Ajout de R1, le nombre de voisin vivant est forcément égale à nb_voisins - 3

    //Pour R2, et R3 on crée deux cas :
    //string regle_2 = to_string(to_alphabet(nb_voisins - 2)) + "2";
    string regle_2;
    regle_2.push_back(to_alphabet(nb_voisins - 2));
    regle_2.push_back('2'); //un doublet avec nb_voisins_mort est de 2
    //string regle_3 = to_string(to_alphabet(nb_voisins - 3 + 48)) + "3"; //un doublet avec nb_voisins_mort est de 3
    string regle_3;
    regle_3.push_back(to_alphabet(nb_voisins - 3));
    regle_3.push_back('3');
    //On
    string nouvelle_regle;
    int i = 1; //index du tableau débute à 1 car on a déjà ajouté une régle
    int j = 0; // j représente le nombre de voisins mort
    while (j <= nb_voisins)
    {
        //nouvelle_regle = to_string(j) + to_string(nb_voisins - j);
        nouvelle_regle = "";
        nouvelle_regle.push_back(to_alphabet(j));
        nouvelle_regle.push_back(to_alphabet(nb_voisins - j));             //on tous les doublets donc la somme = nb_voisins
        if (nouvelle_regle != regle_2 && nouvelle_regle != regle_3)//  (!(nouvelle_regle == regle_2) && !(nouvelle_regle == regle_3)) // si, dans ce doublet, l'un est égale à une des deux règle du dessus, alors on ne rentre pas dans le if
        {
            //tab[i] = "1" + nouvelle_regle + "0";
            tab[i].push_back('1'); //ajout de la règle si il n'y a ni 2 ni 3 voisins vivants
            tab[i].push_back(nouvelle_regle[0]);
            tab[i].push_back(nouvelle_regle[1]);
            tab[i].push_back('0');
            i++;
        }
        j++;
    }
    return tab;
}
string *generation_regles_Griffeath(const unsigned int nb_voisins, int &m)
{
    //Rappel des règles :
    // une cellule passe de l’état i à i + 1 (modulo 4) dès que i + 1 (modulo 4) est présent dans au moins 3 cellules voisines.

    //etat_depart | 0 (jaune, i) |  1 (orange clair, j) | 2 (orange foncé, k) |  3 (rouge, l) | etat_arrivee

    //EXEMPLE :
    //  013401 --> passe de l'etat 0 à 1 car il y a 3 voisins dans l'état 1 (8 voisins)
    //  004401 --> passe de l'etat 0 à 1 car il y a 4 voisins dans l'état 1 (8 voisins)
    //  12242 --> passe de l'etat 1 à 2  car il y a 4 voisins dans l'état 2 (8 voisins)

    //principe algo : on cherche à obtenir un quadruplet | nb_voisins_0 | nb_voisins_1 | nb_voisins_2 | nb_voisins_3 dont la somme de chacun est égale au nombre de voisins

    string *tab;
    tab = new string[500];

    m = 0;
    string nouvelle_regle = "";
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
                            //tab[m] = "0" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "1";
                            nouvelle_regle.push_back('0');
                            nouvelle_regle.push_back(to_alphabet(i));
                            nouvelle_regle.push_back(to_alphabet(j));
                            nouvelle_regle.push_back(to_alphabet(k));
                            nouvelle_regle.push_back(to_alphabet(l));
                            nouvelle_regle.push_back('0');
                            tab[m] = nouvelle_regle;
                            nouvelle_regle = "";
                            m++;
                        }
                        if (k >= 3) // si etat 2 superieur ou egale à 3, alors on passe de l'etat 1 à 2
                        {
                            //tab[m] = "1" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "2";
                            nouvelle_regle.push_back('1');
                            nouvelle_regle.push_back(to_alphabet(i));
                            nouvelle_regle.push_back(to_alphabet(j));
                            nouvelle_regle.push_back(to_alphabet(k));
                            nouvelle_regle.push_back(to_alphabet(l));
                            nouvelle_regle.push_back('2');
                            tab[m] = nouvelle_regle;
                            nouvelle_regle = "";
                            m++;
                        }
                        if (l >= 3) // si etat 3 superieur ou egale à 3, alors on passe de l'etat 2 à 3
                        {
                            //tab[m] = "2" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "3";
                            nouvelle_regle.push_back('2');
                            nouvelle_regle.push_back(to_alphabet(i));
                            nouvelle_regle.push_back(to_alphabet(j));
                            nouvelle_regle.push_back(to_alphabet(k));
                            nouvelle_regle.push_back(to_alphabet(l));
                            nouvelle_regle.push_back('3');
                            tab[m] = nouvelle_regle;
                            nouvelle_regle = "";
                            m++;
                        }
                        if (i >= 3) // si etat 0 superieur ou egale à 3, alors on passe de l'etat 3 à 0 (car modulo)
                        {
                            //tab[m] = "3" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "0";
                            nouvelle_regle.push_back('3');
                            nouvelle_regle.push_back(to_alphabet(i));
                            nouvelle_regle.push_back(to_alphabet(j));
                            nouvelle_regle.push_back(to_alphabet(k));
                            nouvelle_regle.push_back(to_alphabet(l));
                            nouvelle_regle.push_back('2');
                            tab[m] = nouvelle_regle;
                            nouvelle_regle = "";
                            m++;
                        }
                    }
                }
            }
        }
    }
    return tab;
}

string *generation_regles_Wireworld(const unsigned int nb_voisins, int &m)
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

    string *tab;
    tab = new string[500];

    m = 0;
    string nouvelle_regle = "";
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
                        //tab[m] = "2" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "3"; //Ajout de R1 (pas de condition sur voisinage)
                        nouvelle_regle.push_back('2');
                        nouvelle_regle.push_back(to_alphabet(i));
                        nouvelle_regle.push_back(to_alphabet(j));
                        nouvelle_regle.push_back(to_alphabet(k));
                        nouvelle_regle.push_back(to_alphabet(l));
                        nouvelle_regle.push_back('3');
                        tab[m] = nouvelle_regle;
                        nouvelle_regle = "";
                        m++;
                        //tab[m] = "3" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "1"; //Ajout de R2 (pas de condition sur voisinage)
                        nouvelle_regle.push_back('3');
                        nouvelle_regle.push_back(to_alphabet(i));
                        nouvelle_regle.push_back(to_alphabet(j));
                        nouvelle_regle.push_back(to_alphabet(k));
                        nouvelle_regle.push_back(to_alphabet(l));
                        nouvelle_regle.push_back('1');
                        tab[m] = nouvelle_regle;
                        nouvelle_regle = "";
                        m++;
                        if ((k == 1) || (k == 2)) // si nb_voisins electron tête est de 1 ou 2
                        {
                            tab[m] = "1" + to_string(i) + to_string(j) + to_string(k) + to_string(l) + "2"; // alors passage de l'état conducteur à tête electron
                            nouvelle_regle.push_back('1');
                            nouvelle_regle.push_back(to_alphabet(i));
                            nouvelle_regle.push_back(to_alphabet(j));
                            nouvelle_regle.push_back(to_alphabet(k));
                            nouvelle_regle.push_back(to_alphabet(l));
                            nouvelle_regle.push_back('2');
                            tab[m] = nouvelle_regle;
                            nouvelle_regle = "";
                            m++;
                        }
                    }
                }
            }
        }
    }
    return tab;
}

string *generation_regles_Langton_Loop(int &l) // defintion en extension
{
    string tab[219] = {"000000", "000012", "000020", "000030", "000050", "000063", "000071", "000112", "000122", "000132", "000212", "000220", "000230", "000262", "000272", "000320", "000525", "000622", "000722", "001022", "001120", "002020", "002030", "002050", "002125", "002220", "002322", "005222", "012321", "012421", "012525", "012621", "012721", "012751", "014221", "014321", "014421", "014721", "016251", "017221", "017255", "017521", "017621", "017721", "025271", "100011", "100061", "100077", "100111", "100121", "100211", "100244", "100277", "100511", "101011", "101111", "101244", "101277", "102026", "102121", "102211", "102244", "102263", "102277", "102327", "102424", "102626", "102644", "102677", "102710", "102727", "105427", "111121", "111221", "111244", "111251", "111261", "111277", "111522", "112121", "112221", "112244", "112251", "112277", "112321", "112424", "112621", "112727", "113221", "122244", "122277", "122434", "122547", "123244", "123277", "124255", "124267", "125275", "200012", "200022", "200042", "200071", "200122", "200152", "200212", "200222", "200232", "200242", "200250", "200262", "200272", "200326", "200423", "200517", "200522", "200575", "200722", "201022", "201122", "201222", "201422", "201722", "202022", "202032", "202052", "202073", "202122", "202152", "202212", "202222", "202272", "202321", "202422", "202452", "202520", "202552", "202622", "202722", "203122", "203216", "203226", "203422", "204222", "205122", "205212", "205222", "205521", "205725", "206222", "206722", "207122", "207222", "207422", "207722", "211222", "211261", "212222", "212242", "212262", "212272", "214222", "215222", "216222", "217222", "222272", "222442", "222462", "222762", "222772", "300013", "300022", "300041", "300076", "300123", "300421", "300622", "301021", "301220", "302511", "401120", "401220", "401250", "402120", "402221", "402326", "402520", "403221", "500022", "500215", "500225", "500232", "500272", "500520", "502022", "502122", "502152", "502220", "502244", "502722", "512122", "512220", "512422", "512722", "600011", "600021", "602120", "612125", "612131", "612225", "700077", "701120", "701220", "701250", "702120", "702221", "702251", "702321", "702525", "702720"};
    l = 219;
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
        if (tab[i] <= 9)
            c = tab[i] + '0';
        else
            c = 'A' + tab[i] - 10;
        //cout<<tab[i]<<"=tab[i]\n";
        //cout<<c<<"=c\n";
        tab_de_inten.push_back(c);
    }

    int test = 0;
    int i = 0;
    string st;

    while (i < limit)
    {
        if (trans[i][0] == cel) {
            st = trans[i].substr(1, trans[i].length() - 2); //ici on prélève la partie de la règle qui nous intéresse
            //cout << st << "=st\n";
            //cout << tab_de_inten << "=tab_de_inten\n";
            test = st.compare(tab_de_inten);
            if (test == 0)
            {
                size_t j = (trans[i].length() - 1);
                return trans[i][j];
            }
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
            etatDest = fonctionTrans->comparaison_voisinnage(dep.getVoisinage(i, j, *typeVoisinnage), fonctionTrans->tableau  , *etatDepart, fonctionTrans->taille , etatsPossibles->getNombreEtats());
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
