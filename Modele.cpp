#include "Modele.h"

#include <iostream>
#include "simulateur.h"
// #include "outil.h"

using namespace std;

// ça arrive
char comparaison_voisinnage(string voisins, string *trans, char cel){
    // pour un voisinnage donné on va vérifier si ce voisinnage est dans
    // le tableau de fonction transition si oui on va renvoyer un caractère qui
    // va correspondre à l'état de la cellule à la génération t+1
    int i=0;
    int test=0;
    string st;
    while ( trans[i][0]==cel){
        st=trans[i].substr(1, trans[i].length()-2);
        st.append(st);
        test=st.find(voisins);
        if (test!=-1) {
            size_t j=(trans[i].length()-1);
            return trans[i][j];
        }
        i++;
    }
    return 0;
}

int char_to_int(char * c)
{
    int a = 0;
    int b;
    char * p = c;
    while (*p != '\0'){
        b = *p - '0';
        a = a*10;
        a += b;
        p++;
    }
    return a;
}

void Modele::appliquerTransition(const Configuration &dep, Configuration &dest) const
/* Pour chaque cellule de la configuration de départ, récupère ses voisins, récupère son état, et détermine son état d'arrivée */
{ // ça arrive
    if (dep.getReseauLignes() != dest.getReseauLignes() || dep.getReseauColonnes() != dest.getReseauColonnes()) dest = dep;
    char * etatDepart = new char;
    char etatDest ;
    Etat * e= new Etat;
    int p =0;

    for (int i=0; i<dep.getReseauLignes(); i++)
    {
        for (int j=0; j<dep.getReseauColonnes(); j++)
        {
            while(((regles)[p][0])!=('0' + dep.getEtatCellule(i,j).getIndice())) {
                cout<<(regles)[p][0];
                p++;
            };
            cout<<"pass1";
            sprintf(etatDepart, "%d", dep.getEtatCellule(i,j).getIndice());
            cout<<"pass2";
            etatDest = comparaison_voisinnage(dep.getVoisinage(i,j,*typeVoisinnage), regles + p, *etatDepart);
            cout<<"pass3";
            // e = modele.etatsPossibles[char_to_int(&etatDest)]; // vis-à-vis de la surcharge de l'opérateur [] à revoir
            dest.setEtatCellule(i,j,e);
        }
    }
}



