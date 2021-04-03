

#include "automate.h"

void Etat::setCellule(size_t i, bool val)
{
    valeur[i] = val;
}

std::ostream &operator<<(std::ostream &f, const Etat &e)
{
    for (size_t i = 0; i < e.getDimension(); i++)
        if (e.getCellule(i))
            f << char(178);
        else
            f << " ";
    return f;
}

Etat &Etat::operator=(const Etat &e)
{
    if (this != &e)
    {
        if (Dimension != e.Dimension)
        {
            bool *newvaleur = new bool[e.Dimension];
            for (size_t i = 0; i < e.Dimension; i++)
            {
                newvaleur[i] = e.valeur[i];
            }
            bool *old = valeur;
            valeur = newvaleur;
            Dimension = e.Dimension;
            delete[] old;
        }
        else
        {
            for (size_t i = 0; i < e.Dimension; i++)
            {
                valeur[i] = e.valeur[i];
            }
        }
        return *this;
    }
}

void Automate::appliquerTransition(const Etat &dep, Etat &dest) const
{
    if (dep.getDimension() != dest.getDimension())
        dest = dep;
    for (size_t i = 0; i < dep.getDimension(); i++)
    {
        unsigned short conf = 0;
        if (i < 0)
            conf += dep.getCellule(i - 1) * 4;
        conf += dep.getCellule(i) * 2;
        if (i < dep.getDimension() - 1)
            conf += dep.getCellule(i + 1);
        dest.setCellule(i, numeroBit[7 - conf] - '0');
    }
}
unsigned short NumBitToNum(const std::string &num)
{
    if (num.size() != 8)
        throw AutomateException("Numero d’automate indefini");
    int puissance = 1;
    unsigned short numero = 0;
    for (int i = 7; i >= 0; i--)
    {
        if (num[i] == '1')
            numero += puissance;
        else if (num[i] != '0')
            throw AutomateException("Numero d’automate indefini");
        puissance *= 2;
    }
    return numero;
}
std::string NumToNumBit(unsigned short num)
{
    std::string numeroBit;
    if (num > 256)
        throw AutomateException("Numero d’automate indefini");
    unsigned short p = 128;
    int i = 7;
    while (i >= 0)
    {
        if (num >= p)
        {
            numeroBit.push_back('1');
            num -= p;
        }
        else
        {
            numeroBit.push_back('0');
        }
        i--;
        p = p / 2;
    }
    return numeroBit;
}
