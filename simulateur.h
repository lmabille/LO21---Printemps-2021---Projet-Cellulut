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
    int buffer_config;
    int clock;
    Modele const & modele;
    static Simulateur *instance_unique;
    Simulateur();
    Simulateur(const Simulateur &) = delete;
    void operator=(const Simulateur &) = delete;
    static Simulateur *uniqueInstance;
    friend class Configuration;

public:
    static Simulateur &donneInstance();
    static void libereInstance();
    void affichage();
    void reset();
    void next();
    string& getVoisinage(int i, int j, const Configuration& config, Case* ensemble_case) const;
    Configuration& appliquerTransition(const Configuration &dep) const;

};

#endif