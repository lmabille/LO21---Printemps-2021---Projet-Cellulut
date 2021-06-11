//
// Created by thoma on 13/05/2021.
//

#include "voisinage.h"


//Voisinage::Voisinage(int n) : nbCelluleVoisi(n), ensemble_case(new Case[n]()) { typeVoisi = ""; }

Voisinage::Voisinage() : nbCelluleVoisi(10), ensemble_case(new Case[10]()) { typeVoisi = ""; }
/*
V_ChoixUtilisateur::V_ChoixUtilisateur(int n) {
    this->nbCelluleVoisi = n;
    this->ensemble_case = new Case[n]();
    this->setType("");
}*/ //: nbCelluleVoisi(n), ensemble_case(new Case[n]()) { typeVoisi = ""; }


void V_VonNeumann::definir_ensemble_case(int rayon)
{
    nbCelluleVoisi = 4*rayon;
    ensemble_case = new Case[nbCelluleVoisi]; // on réserve la place pour 4*rayon cellules
    int ind = 0;
    for (int r=1; r<=rayon; r++) // pour chaque couronne on remplit les 4 cases concernées
    {
        ensemble_case[ind].setL_C(0,-r); // gauche
        ensemble_case[ind+1].setL_C(r,0); // haut
        ensemble_case[ind+2].setL_C(0,r); // droite
        ensemble_case[ind+3].setL_C(-r, 0); // bas
        ind += 4;
    }
    /*for (unsigned int i=0;i<nbCelluleVoisi;i++)
        cout << "[" << ensemble_case[i].getL() << "," << ensemble_case[i].getC() << "] ";*/ // ok

}

void V_Moore::definir_ensemble_case(int rayon)
{
    nbCelluleVoisi = (2*rayon +1)*(2*rayon +1) - 1;
    //cout << "*** " << nbCelluleVoisi << " cases reservees ***" << endl; // ok

    ensemble_case = new Case[nbCelluleVoisi]; // on réserve la place pour le bon nombre de cellules

    int ind = 0;

    for (int r=1; r<= rayon; r++)
    {
        //cout << "\tcouronne " << r << endl;

        //cout << " ligne du haut (coins inclus) " << endl;
        for (int j=-r; j<=r; j++)
        {
            //cout << ind;
            ensemble_case[ind].setL_C(r,j);
            //cout << "[" << ensemble_case[ind].getL() << "," << ensemble_case[ind].getC() << "] ";
            ind++;
        }
        //cout << endl;

        //cout << "ligne de droite (coins exclus)" << endl;
        for (int i=r-1; i>=-r+1; i--)
        {
            //cout << ind;
            ensemble_case[ind].setL_C(i,r);
            //cout << "[" << ensemble_case[ind].getL() << "," << ensemble_case[ind].getC() << "] ";
            ind++;
        }
        //cout << endl;

        //cout << "ligne du bas (coins inclus)" << endl;
        for (int j=r; j>=-r; j--)
        {
            //cout << ind;
            ensemble_case[ind].setL_C(-r,j);
            //cout << "[" << ensemble_case[ind].getL() << "," << ensemble_case[ind].getC() << "] ";
            ind++;
        }
        //cout << endl;

        //cout << "ligne de gauche (coins exclus)" << endl;
        for (int i=-r+1; i<=r-1; i++)
        {
            //cout << ind;
            ensemble_case[ind].setL_C(i,-r);
            //cout << "[" << ensemble_case[ind].getL() << "," << ensemble_case[ind].getC() << "] ";
            ind++;
        }
        //cout << endl;
    }

}

void V_ChoixUtilisateur::ajouter_case(size_t i, size_t j)
{
    // par l'utilisateur + compter le nombre de cases sélectionnées. Remplir le tableau avec ces indications.
    Case* oldTab = ensemble_case;
    Case* newTab = new Case[nbCelluleVoisi+1];
    for (size_t i=0; i<nbCelluleVoisi; i++)
    {
        newTab[i] = ensemble_case[i];
    }
    newTab[nbCelluleVoisi].setL_C(i,j);
    ensemble_case = newTab;
    delete[] oldTab;
    nbCelluleVoisi++;
}

void V_ChoixUtilisateur::definir_ensemble_case(int rayon)
{

};

size_t Voisinage::getNbCelluleVoisi() const
{
    return this->nbCelluleVoisi;
}

const string Voisinage::getTypeVoisi()
{
    return this->typeVoisi;
}

/*
void Voisinage::setNbCellule(int nb)
{
    this->nbCelluleVoisi = nb;
    /*if (nb >= 0)
        this->nbCelluleVoisi = nb;
    else
        cout << "Nombre négatif. Erreur" << endl;*/


//Ne pas commenter j'en ai besoin svp ;)
Case *Voisinage::getTableau()
{
    return this->ensemble_case;
}


Case &Voisinage::operator[](int indice)
{
    try
    {
        if (indice < 0 || indice >= nbCelluleVoisi)
            throw string("case n'existe pas !"); // à remplacer par AutomateException comme dans le td
        else
            return ensemble_case[indice];
    }
    catch (string const &erreur)
    {
        cout << erreur << endl;
    }

}




