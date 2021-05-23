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

// configuration = matrice de cellules
