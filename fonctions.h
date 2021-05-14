#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <iostream>
#include <cstdio>

using namespace std;


class Reseau {
    int Longueur;
    int Largeur;
    friend Configuration;
    Reseau()=default;
    Reseau(int lon=0, int lar=0) : Longueur(lon), Largeur(lar) {};

public:
    int get_long(){return Longueur;};
    int get_larg(){return Largeur; }
};

class Configuration {
private:
    size_t dimension;
    bool* valeur = nullptr;
public:
    Etat(size_t n=0);
    Etat(const Etat& e);
    ~Etat();
    Etat& operator=(const Etat& e);
    void setCellule(size_t i, bool val);
    bool getCellule(size_t i) const;
    size_t getDimenstion() const;

};

#endif // FONCTIONS_H_INCLUDED
