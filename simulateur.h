#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_SIMULATEUR_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_SIMULATEUR_H
#include <string>
#include "Modele.h"
#include "etat.h"
#include "configuration.h"
#include "voisinage.h"
#include <iostream>

using namespace std;
class Simulateur
{
private:
    Modele const & modele;
    Configuration** configurations = nullptr;
    const Configuration* configurationDepart = nullptr;
    size_t rang = 0;
    size_t tailleBuffer;
    void build(size_t caseBuf);
    // int clock; pas temporel de next() , à voir
    Simulateur(const Simulateur &) = delete;
    void operator=(const Simulateur &) = delete;
    static Simulateur *uniqueInstance ;
    //

public:
    Simulateur(const Modele &m, size_t buf = 2);//remettre en private
    Simulateur(const Modele &m, const Configuration& dep, size_t buf = 2);
    ~Simulateur();
    void setConfigDepart(const Configuration& config); // définit une configuration de départ
    void next(); // applique la fonction de transition du modèle sur une génération
    void run(size_t nbSteps); // applique la fonction de transition du modèle sur un nombre de générations donnés (nbSteps)
    const Configuration& getLastConfig() const; // renvoie la dernière configuration enregistrée
    size_t getRangLast() const; // renvoie le rang de la simulation cad le nombre de générations qui ont été simulées
    void reset(); // revient à l'état de départ de la simulation

    // Iterateur pour parcourir les simulations enregistrées en lecture et en écriture

    static Simulateur &donneInstance(Modele & m, size_t buffer);
    static void libereInstance();
};

#endif