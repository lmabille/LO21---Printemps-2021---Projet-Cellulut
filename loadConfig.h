
#ifndef LO21_PRINTEMPS_2021_PROJET_CELLULUT_LOADCONFIG_H
#define LO21_PRINTEMPS_2021_PROJET_CELLULUT_LOADCONFIG_H

#include <string>
#include <cstdio>
#include "voisinage.h"
#include "etat.h"
#include "configuration.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"



string * getListeConfig(const char* nom_fichier);
int getNbConfig(const char* nom_fichier);
Configuration * chargerConfiguration(const char* nomFichier , string nomConfig);

#endif //LO21_PRINTEMPS_2021_PROJET_CELLULUT_LOADCONFIG_H
