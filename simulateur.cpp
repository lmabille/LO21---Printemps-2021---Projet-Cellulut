/**
 * @file simulateur.cpp
 * @author Laurine Hamard
 * @brief
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include "simulateur.h"

using namespace std;

/**
 * @brief Constructeur d'un simulateur
 *
 * @param[in] mod�le en cour
 * @param[in] taille du buffer
 */
Simulateur::Simulateur(const Modele &m, size_t buf): modele(m), tailleBuffer(buf)
{
    configurations = new Configuration*[tailleBuffer];
    for (size_t i = 0; i<tailleBuffer; i++) configurations[i] = nullptr;
}


/**
 * @brief Constructeur d'un simulateur
 *
 * @param[in] mod�le en cour
 * @param[in] configuration de d�part
 * @param[in] taille du buffer
 */
Simulateur::Simulateur(const Modele &m, const Configuration& dep, size_t buf): modele(m), tailleBuffer(buf)
{
    configurations = new Configuration*[tailleBuffer];
    for (size_t i = 0; i<tailleBuffer; i++) configurations[i] = nullptr;
    configurations[0] = new Configuration(dep);
}

/**
 * @brief setter de configuration de d�part
 *
 * @param[in] nouvelle configuration
 */
void Simulateur::setConfigDepart(Configuration& config)
{
    configurationDepart = &config;
    reset();
}

/**
 * @brief Fonction pour passer � la configuration suivante
 *
 *
 */
void Simulateur::next()
{
    if (configurationDepart == nullptr) throw AutomateException("Etat depart indefini ! \n"); // d�finir classe automate exception
    rang++;
    build(rang%tailleBuffer);
    modele.appliquerTransition(*configurations[(rang-1)%tailleBuffer], *configurations[rang%tailleBuffer]);
}

/**
 * @brief lancement du simulateur pour N it�ration
 *
 * @param[in] nombre d'�tat � parcourir
 */

void Simulateur::run(size_t nbSteps)
{
    for (size_t i = 0; i<nbSteps;i++) next();
}


/**
 * @brief getter de la derni�re configuration
 *
 * @return derniere configuration
 */
const Configuration& Simulateur::getLastConfig() const
{
    return *configurations[rang%tailleBuffer];
}

/**
 * @brief getter du rang de la derni�re configuration
 *
 * @return derniere configuration
 */
size_t Simulateur::getRangLast() const
{
    return rang;
}


/**
 * @brief retour � la configuration de d�part
 *
 * @return void
 */
void Simulateur::reset()
{
    if (configurationDepart == nullptr) throw AutomateException("Etat depart indefini !\n");
    rang = 0;
    build(0);
    configurations[0] = configurationDepart;
}

/**
 * @brief destructeur du simulateur
 *
 *
 */

Simulateur::~Simulateur()
{
    for (size_t i =0; i<tailleBuffer;i++) delete configurations[i];
    delete[] configurations;
}


/**
 * @brief ajout d'une configuration au buffer
 *
 * @param[in] rang de la nouvelle configuration
 */
void Simulateur::build(size_t caseBuf)
{
    if (caseBuf>=tailleBuffer) throw AutomateException("Erreur taille buffer !\n");
    if (configurations[caseBuf] == nullptr) configurations[caseBuf] = new Configuration;
}


/**
 * @brief getter de l'instance du simulateur
 *
 * @param[in] mod�le du simulateur
 * @param[in] une taille de buffer
 */
Simulateur &Simulateur::donneInstance(Modele & m, size_t buffer)
{
    if (uniqueInstance == nullptr)
        uniqueInstance = new Simulateur(m, buffer);
    return *uniqueInstance;
}


/**
 * @brief lib�rer l'instance du simulateur
 *
 *
 */
void Simulateur::libereInstance()
{
    delete uniqueInstance;
    uniqueInstance = nullptr;
}




