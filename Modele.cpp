#include "Modele.h"

#include <iostream>
#include "simulateur.h"
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
    cout << "compa_vois"
         << "\n";
    while (i < limit && trans[i][0] == cel)
    {
        cout << "passeboucle"
             << "\n";
        st = trans[i].substr(1, trans[i].length() - 2);
        cout << st << "\n";
        st.append(st);
        cout << st << "\n";
        cout << voisins << "\n";
        test = st.find(voisins);
        if (test != -1)
        {
            size_t j = (trans[i].length() - 1);
            cout << trans[i][j];
            return trans[i][j];
        }
        //il ne faut pas avancé dans le tableaux si il est vide donc rajouter un attribut "nombre de règles" dans FonctiondeTransition
        i++;
    }
    return 0;
}

int char_to_int(char *c)
{
    int a = 0;
    int b;
    char *p = c;
    while (*p != '\0')
    {
        b = *p - '0';
        a = a * 10;
        a += b;
        p++;
    }
    return a;
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
    cout << "passe1"
         << "\n";

    for (int i = 0; i < dep.getReseauLignes(); i++)
    {
        for (int j = 0; j < dep.getReseauColonnes(); j++)
        {
            while (p < fonctionTrans->taille && ((int)((fonctionTrans->tableau)[p][0]) != ('0' + dep.getEtatCellule(i, j).getIndice())))
            {
                p++;
            };
            sprintf(etatDepart, "%d", dep.getEtatCellule(i, j).getIndice());
            cout << dep.getVoisinage(i, j, *typeVoisinnage) << "\n";
            etatDest = comparaison_voisinnage(dep.getVoisinage(i, j, *typeVoisinnage), fonctionTrans->tableau + p, *etatDepart, fonctionTrans->taille - p);
            cout << etatDest;
            //e = etatsPossibles[char_to_int(&etatDest)]; // vis-à-vis de la surcharge de l'opérateur [] à revoir
            dest.setEtatCellule(i, j, e);
        }
    }
}

#include "Modele.h"

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
}
