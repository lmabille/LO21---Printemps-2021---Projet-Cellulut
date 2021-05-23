#include <iostream>
#include "simulateur.h"

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

string& Simulateur::getVoisinage(int i, int j, Configuration& config, Case* ensemble_case)
{
    /* pour chaque �l�ment du tableau ensemble de cases,
       r�cup�re le x et le y puis va dans le tableau configuration
       et r�cup�re l'�tat de la cellule i+x, j+y, stocke cet �tat
       dans un tableau de caract�res, retourne ce tableau */

    char* ptr = ensemble_case;
    string voisinage = nullptr;
    int x, y;
    int ind = 0;

    while (ptr != nullptr)
    {
        x = ptr->x;
        y = ptr->y;
        voisinage[ind] = Configuration::getEtat(i+x, j+y);
        ptr ++;
        ind ++;
    }
    return voisinage;
}

char comparaison_voisinnage(string voisins, string trans[], char cel){

    /*pour un voisinnage donn� on va v�rifier si ce voisinnage est dans
     * le tableau de fonction transition si oui on va renvoyer un charact�re qui
     * va correspondre � l'�tat de la cellule � la g�n�ration t+1*/
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

// configuration = matrice de cellules
