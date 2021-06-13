/**
 * @file informations.cpp
 * @author Orhane Lahneche (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "informations.h"
#include "ui_informations.h"
/**
 * @brief Construit un objet de la classe information
 * 
 * @param[out] parent 
 * @param[in] nomFctTrans nom de la fonction de transition
 * @param[in] V nom du voisinage utilisé
 * @param[in] e ensemble des états correspondants 
 * @param[in] typeFcttrans en intension ou en extension 
 */
informations::informations(QWidget *parent, string nomFctTrans, Voisinage *V, EnsembleEtats *e, string typeFcttrans) : QDialog(parent),
                                                                                                                       ui(new Ui::informations),
                                                                                                                       nomFctTrans(nomFctTrans),
                                                                                                                       V(V),
                                                                                                                       e(e),
                                                                                                                       typeFcttrans(typeFcttrans)
{
    ui->setupUi(this);
}
/**
 * @brief Destructeur de la classe information
 * 
 */
informations::~informations()
{
    delete ui;
}

/**
 * @brief 
 * 
 */
void informations::enregistrerModele()
{
    //enregistrement des infos manquantes du modèle
    string *tab;
    int nbregle = 0;
    int nbVoisin = V->getNbCelluleVoisi();

    //génération des règles correspondant à la bonne fonction de transition
    if (nomFctTrans == "Game Of Life")
    {
        std::cout << "on est laa";
        tab = generation_regles_Life_game(nbVoisin, nbregle);
    }
    else if (std::strcmp(nomFctTrans.c_str(), "WireWorld") == 0)
        tab = generation_regles_Wireworld(nbVoisin, nbregle);
    else if (std::strcmp(nomFctTrans.c_str(), "Langton's Loop") == 0)
        tab = generation_regles_Langton_Loop(nbregle);
    else if (std::strcmp(nomFctTrans.c_str(), "Automate circulaire de Griffeath") == 0)
        tab = generation_regles_Griffeath(nbVoisin, nbregle);
    else if (std::strcmp(nomFctTrans.c_str(), "Brian's Brain") == 0)
        tab = generation_regles_Brians_Brain(nbVoisin, nbregle);
    else if (std::strcmp(nomFctTrans.c_str(), "Wireworld") == 0)
        tab = generation_regles_Wireworld(nbVoisin, nbregle);

    FonctionTransition *f;

    if (typeFcttrans == "extension")
        f = new FonctionTransition(tab, nbregle);
    else
        f = new FonctionTransitionIntention(tab, nbregle);

    auto m = new Modele((this->ui->lineEdit->text()).toStdString(), e, f, typeFcttrans, V, (this->ui->textEdit->toPlainText()).toStdString(), (this->ui->lineEdit_2->text()).toStdString(), 2021);

    m->sauvegardeM(); //sauvegarde du modèle

    auto Menu = new MenuPrincipale_2;

    Menu->show(); //on réouvre le menu principal

    this->close(); //et enfin on ferme la page
}
