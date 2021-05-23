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
    /* pour chaque élément du tableau ensemble de cases,
       récupère le x et le y puis va dans le tableau configuration
       et récupère l'état de la cellule i+x, j+y, stocke cet état
       dans un tableau de caractères, retourne ce tableau */

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
