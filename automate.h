#ifndef _AUTOMATE_H
#define _AUTOMATE_H
#include <string>
#include <iostream>

using namespace std;

class AutomateException
{
public:
    AutomateException(const std::string &message) : info(message) {}
    std::string getInfo() const { return info; }

private:
    std::string info;
};
#endif

class Etat
{

    size_t Dimension = 0;
    bool *valeur;

public:
    size_t getDimension() const
    {
        return Dimension;
    }
    bool getCellule(size_t i) const
    {
        if ((i >= 0) && (i <= (Dimension - 1)))
        {
            return valeur[i];
        }
    }
    void setCellule(size_t i, bool val)
    {
        valeur[i] = val;
    }
    Etat() = default;
    Etat(size_t i) : Dimension(i)
    {
        if (i)
        {
            for (size_t j = 0; j < i; j++)
            {
                valeur[j] = 0;
            }
        }
    }
    Etat(const Etat &e)
    {
        valeur = new bool[e.Dimension];
        for (size_t i = 0; i < e.Dimension; i++)
        {
            valeur[i] = e.valeur[i];
        }
    }
};

class Automate
{
    unsigned int numero;
    string numeroBit;

public:
    unsigned short getNumero() const { return numero; }
    string getNumeroBit() const { return numeroBit; }
    ostream &operator<<(ostream &s, const Automate &a);
    void Automate::appliquerTransition(const Etat &dep, Etat &dest) const;
};

class Simultateur
{
    const Automate &automate;
    Etat **etats = nullptr;
    const Etat *depart = nullptr;
    size_t nbMaxEtats;
    size_t rang = 0;
    void build(size_t c);

public:
    Simulateur
}