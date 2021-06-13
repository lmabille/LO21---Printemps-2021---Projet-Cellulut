/**
 * @file menuprincipale_2.cpp
 * @author Orhane Lahneche
 * @brief
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "menuprincipale_2.h"
#include "ui_menuprincipale_2.h"

/**
 * @brief constructeur de la classe MenuPrincipale_2
 *
 * @param[in] dep configuration de départ sur laquelle on va appliquer la transition
 * @param[out] parent fenêtre parente du lenu principal
 * @return une fenêtre menuprincipale dans la fenêtre parent
 */
MenuPrincipale_2::MenuPrincipale_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuPrincipale_2)
{
    ui->setupUi(this);
}


/**
 * @brief destructeur de la classe menuprincipale_2
 *
 * @return detruit l'objet
 */
MenuPrincipale_2::~MenuPrincipale_2()
{
    delete ui;
}

/**
 * @brief affichage du menu des modèles à la suite d'un clique sur le bouton "choisir modèle"
 *
 * @return ouvre une fenêtre Choix_Modele et ferme le menu principal
 */
void MenuPrincipale_2::afficherModeles()
{
    Choix_Modele * Menu = new Choix_Modele;
    Menu->show();
    this->close();
}


/**
 * @brief affichage du menu des fonction de transition à la suite d'un clique sur le bouton "créer modèle"
 *
 * @return ouvre une fenêtre choixTransition et ferme le menu principal
 */
void MenuPrincipale_2::afficher_choix_transition(){
    choixTransition * ct = new choixTransition;
    ct->show();
    this->close();
};
