#include <iostream>
#include "simulateur.h"

using namespace std;

Simulateur &Simulateur::donneInstance()
{
    if (uniqueInstance == nullptr)
        uniqueInstance = new Simulateur();
    return *uniqueInstance;
}

void Simulateur::libereInstance()
{
    delete uniqueInstance;
    uniqueInstance = nullptr;
}

string& Simulateur::getVoisinage(int i, int j, const Configuration& config, Case* ensemble_case) const
{
    /* pour chaque �l�ment du tableau ensemble de cases,
       r�cup�re le x et le y puis va dans le tableau configuration
       et r�cup�re l'�tat de la cellule i+x, j+y, stocke cet �tat
       dans un tableau de caract�res, retourne ce tableau */

    Case* ptr = ensemble_case;
    string voisinage = nullptr;
    int x, y;
    int ind = 0;

    while (ptr != nullptr)
    {
        x = ptr->getX();
        y = ptr->gety();
        voisinage[ind] = config.grille[i+x][j+y].get_Etat().getIndice();
        ptr ++;
        ind ++;
    }
    return voisinage;
}

char comparaison_voisinnage(string voisins, string trans[], char cel){
    /* pour un voisinnage donn� on va v�rifier si ce voisinnage est dans
     * le tableau de fonction transition si oui on va renvoyer un caract�re qui
     * va correspondre � l'�tat de la cellule � la g�n�ration t+1 */

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

Configuration& Simulateur::appliquerTransition(const Configuration &dep) const
/* Pour chaque cellule de la configuration de d�part, r�cup�re ses voisins, r�cup�re son �tat, et d�termine son �tat d'arriv�e */
{
    Configuration config = dep;
    char * etatDepart;
    char etatDest;
    Etat * e= new Etat;

    for (int i=0; i<dep.reseau->get_long(); i++)
    {
        for (int j=0; j<dep.reseau->get_larg(); j++)
        {
            sprintf(etatDepart, "%d", dep.grille[i][j].get_Etat().getIndice());
            etatDest = comparaison_voisinnage(getVoisinage(i,j,dep,modele.typeVoisinnage.ensemble_case), fonctionTrans->tableau, etatDepart);
            e = Modele.ensembleEtat[char_to_int(&etatDest)];
            dest[i][j].set_etat(&e);
        }
    }

    return config;
}



