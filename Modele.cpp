#include "Modele.h"

#include <iostream>
#include "simulateur.h"
// #include "outil.h"

using namespace std;

// ça arrive
char comparaison_voisinnage(string voisins, string *trans, char cel, unsigned int limit){
    // pour un voisinnage donné on va vérifier si ce voisinnage est dans
    // le tableau de fonction transition si oui on va renvoyer un caractère qui
    // va correspondre à l'état de la cellule à la génération t+1
    int i=0;
    int test=0;
    string st;
    cout<<"compa_vois"<<"\n";
    while ( i<limit && trans[i][0]==cel){
        cout<<"passeboucle"<<"\n";
        st=trans[i].substr(1, trans[i].length()-2);
        cout<<st<<"\n";
        st.append(st);
        cout<<st<<"\n";
        cout<<voisins<<"\n";
        test=st.find(voisins);
        if (test!=-1) {
            size_t j=(trans[i].length()-1);
            cout<<trans[i][j];
            return trans[i][j];
        }
        //il ne faut pas avancé dans le tableaux si il est vide donc rajouter un attribut "nombre de règles" dans FonctiondeTransition
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
/* Pour chaque cellule de la configuration de départ, récupère ses voisins, récupère son état, et détermine son état d'arrivée qu'elle place dans la confifuration de destinationn*/
{
    if (dep.getReseauLignes() != dest.getReseauLignes() || dep.getReseauColonnes() != dest.getReseauColonnes()) dest = dep;
    char * etatDepart = new char;
    char etatDest ;
    Etat * e= new Etat;
    unsigned int p =0;
    cout<<"passe1"<<"\n";

    for (int i=0; i<dep.getReseauLignes(); i++)
    {
        for (int j=0; j<dep.getReseauColonnes(); j++)
        {
            while(p<fonctionTrans->taille && ((int)((fonctionTrans->tableau)[p][0])!=('0' + dep.getEtatCellule(i,j).getIndice()))) {
                p++;
            };
            sprintf(etatDepart, "%d", dep.getEtatCellule(i,j).getIndice());
            cout<<dep.getVoisinage(i,j,*typeVoisinnage)<<"\n";
            etatDest = comparaison_voisinnage(dep.getVoisinage(i,j,*typeVoisinnage), fonctionTrans->tableau + p, *etatDepart, fonctionTrans->taille-p);
            cout<<etatDest;
            //e = etatsPossibles[char_to_int(&etatDest)]; // vis-à-vis de la surcharge de l'opérateur [] à revoir
            dest.setEtatCellule(i,j,e);
        }
    }
}



