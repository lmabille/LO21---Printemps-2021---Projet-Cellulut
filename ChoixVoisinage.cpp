/**
 * @file ChoixVoisinage.cpp
 * @author Violette Durocher
 * @brief Fichier fournissant les methodes de la classe ChoixVoisinage afin de permettre a l'utilisateur de parametrer son voisinage
 * @version 0.1
 * @date 2021-06-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "ChoixVoisinage.h"


/**
 * @brief Constructeur de la classe ChoixVoisinage
 *
 * @param[in] parent Fenetre ChoixTransition qui precede et appelle la creation de cette fenetre ChoixVoisinage
 * @param[in] trans Nom de la fonction de transition selectionnee dans la fenetre ChoixTransition
 * @param[in] L Nombre de lignes maximal -> determine le rayon maximal du voisinage
 * @param[in] C Nombre de colonnes maximal -> determine le rayon maximal du voisinage
 * @return   Fenetre ChoixVoisinage permettant le parametrage du voisinage pour un modele
 */
ChoixVoisinage::ChoixVoisinage(QWidget* parent, std::string trans, size_t L, size_t C): transition(trans)
{
    /*** GRILLE ***/

    size_t tailleCell = 15; // taille cellule

    setRayonMax(L,C); // calcul du rayon maximal du voisinage en fonction des dimensions L et C passees en arguments

    calculCoordMiddleCell(); // calcul des coordonnées de la cellule du milieu

    size_t dimSide = calculDimSide(); // dimensions maximales de l'affichage en fonction du rayon

    visu = new QTableWidget(dimSide, dimSide);
    visu->setFixedSize(2.61*tailleCell*dimSide, 1.61*tailleCell*dimSide);

    // enlever les labels et les scrollbars
    visu->horizontalHeader()->setVisible(false);
    visu->verticalHeader()->setVisible(false);
    visu->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    visu->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (size_t i=0; i<dimSide; i++)
    {
        for (size_t j=0; j<dimSide; j++)
        {
            visu->setRowHeight(i,tailleCell);
            visu->setColumnWidth(j,tailleCell);
            visu->setItem(i,j, new QTableWidgetItem(""));
            if (i==lineMiddleCell && j==collumnMiddleCell) visu->item(i,j)->setData(Qt::BackgroundRole, QColor(255,0,0)); // cellule du centre
            else visu->item(i,j)->setData(Qt::BackgroundRole, QColor(255,255,255)); // à la création, toutes les cellules sont blanches sauf celle du centre
        }
    }

    // Message recharge
    indication = new QLabel;
    indication->setVisible(false);

    // choix du rayon (choixRayon)
    choixRayon = new QSpinBox();
    choixRayon->setRange(1,rayonMax);
    choixRayon->setVisible(false);
    connect(choixRayon, SIGNAL(valueChanged(int)),this,SLOT(chargerAppercu()));

    // layout
    affichage = new QHBoxLayout;
    affichage->addWidget(visu);
    affichage->addWidget(choixRayon);
    affichage->addWidget(indication);


    /*** PARAMETRES ***/

    listeVois = new QComboBox();

    if (transition=="Langton's Loop")
    {
        // langston's loop fonctionne uniquement avec un voisiange de Von Neumann de rayon 1
        listeVois->insertItem(0,"Von Neumann");
        choixRayon->setMaximum(1);
    }
    else
    {
        listeVois->insertItem(0,"Von Neumann");
        listeVois->insertItem(1,"Moore");
        listeVois->insertItem(2,"Personnalise");
    }

    connect(listeVois, SIGNAL(currentIndexChanged(int)),this, SLOT(indexChanged(int)));

    // layout
    parametres = new QHBoxLayout();
    parametres->addWidget(listeVois);


    /*** ACTIONS ***/

    // retour = new QPushButton("Retour"); // non disponible pour l'instant
    validation = new QPushButton("Valider");
    connect(validation,SIGNAL(clicked()),this,SLOT(enregistrerChoixVoisinage()));

    // Layout
    actions = new QHBoxLayout;
    // actions->addWidget(retour);
    actions->addWidget(validation);

    // Layout final (fenetre)
    fenetre = new QVBoxLayout;

    fenetre->addLayout(parametres);
    fenetre->addLayout(affichage);
    fenetre->addLayout(actions);

    setLayout(fenetre);

    // par défaut on affiche von neumann
    chargerAppercu();

}


/**
 * @brief Calcule le rayon max disponible pour les voisinages en fonction des dimensions passees en argument du constructeur
 *
 * @param[in] nbLignesReseau Nombre de lignes maximal du reseau sur lequel s'appliquera ce modele
 * @param[in] trans Nombre de colonnes maximal du reseau sur lequel s'appliquera ce modele
 * @return   void
 */
void ChoixVoisinage::setRayonMax(size_t nbLignesReseau, size_t nbColonnesReseau)
{
    size_t actualSide = min(nbLignesReseau, nbColonnesReseau);
    if (actualSide%2 == 1) // impair
    {
        rayonMax = actualSide/2; // actualSide est un entier donc renvoie une division entière
    }
    else
    {
        rayonMax = (actualSide - 1)/2;
    }
}


/**
 * @brief Calcule les dimensions de l'affichage carre de l'appercu en fonction du rayonMax
 *
 * @return   Dimension (x=y) de l'appercu selon le rayonMax
 */
size_t ChoixVoisinage::calculDimSide ()
{
    size_t dimSide = rayonMax*2 + 1;
    return dimSide;
}


/**
 * @brief Remet a blanc l'apercu (cases noires -> blanc)
 *
 * @return   void
 */
void ChoixVoisinage::cleanAppercu()
{
    size_t dimSide = calculDimSide();
    for (size_t i=0;i<dimSide;i++)
    {
        for (size_t j=0;j<dimSide;j++)
        {
            if (visu->item(i,j)->background().color() == QColor(0,0,0))
            {
                visu->item(i,j)->setData(Qt::BackgroundRole,QColor(255,255,255));
            }
        }
    }
}


/**
 * @brief Affiche l'appercu en fonction du voisinage et du rayon selectionne par l'utilisateur
 *
 * @return   void
 */
void ChoixVoisinage::chargerAppercu()
{
    cleanAppercu(); // on remet l'aperçu à blanc

    int index = listeVois->currentIndex();

    if (index==0 || index==1) // Le rayon est variable pour les voisinages de Von Neumann et Moore
    {
        choixRayon->setVisible(true);
    }

    int rayonChoisi = choixRayon->value();
    quelVoisinage(index, rayonChoisi); // on crée l'objet voisinage en fonction du choix de l'utilisateur

    if (index==0 || index==1) // moore ou von neuman
    {
    // on colorie les cases en fonction du tableau de cases déjà rempli dans ces deux voisinages
        Case* coordonneesAColorier = choice->getTableau();
        int nombreCases = choice->getNbCelluleVoisi();

        size_t dimSide = calculDimSide();
        for (int p = 0; p<nombreCases; p++)
        {
            for (size_t i=0;i<dimSide;i++)
            {
                for (size_t j=0;j<dimSide;j++)
                {
                    if (i==lineMiddleCell+coordonneesAColorier[p].getL() && j==collumnMiddleCell+coordonneesAColorier[p].getC())
                    {
                        visu->item(i,j)->setData(Qt::BackgroundRole,QColor(0,0,0));
                    }
                }
            }
        }
    }
    else // personnalise = choix utilisateur
    {
        // on demande à l'utilisateur de choisir ses cases
        indication->setText("Cliquez sur les voisines");
        afficherMessage();

        choixRayon->setVisible(false);
        connect(visu, SIGNAL(cellClicked(int,int)), this, SLOT(colorierCase(int,int))); // les cases selectionnes deviennent noires
    }

    delete choice; // appel du constructeur du voisinage pour liberer la memoireapres chaque affichage
    choice = nullptr;
}


/**
 * @brief Construit un voisinage et le stocke dans l'attribut Voisinage de la classe ChoixVoisinage temporairement afin de recuperer son ensemble de cases
 *
 * @param[in] i Index selectionne de la QComboBox au moment ou la fonction est appelee
 * @param[in] rayon Rayon selectionnee au moment ou la fonction est appelee
 * @return   void
 */
void ChoixVoisinage::quelVoisinage(int i, size_t rayon)
{
    switch(i)
    {
    case 0: // Von Neumann
    {
        V_VonNeumann* vN = new V_VonNeumann();
        vN->definir_ensemble_case(rayon); // on remplit l'ensemble de cases
        choice = static_cast <V_VonNeumann*> (vN);
        break;
    }
    case 1: // Moore
    {
        V_Moore* vM = new V_Moore();
        vM->definir_ensemble_case(rayon); // on remplit l'ensemble de cases
        choice = static_cast <V_Moore*> (vM);
        break;
    }
    case 2:
    {
        V_ChoixUtilisateur* vU = new V_ChoixUtilisateur();
        vU->definir_ensemble_case(rayon); // cette fonction ne fait rien
        choice = static_cast <V_ChoixUtilisateur*> (vU);
        break;
    }
    }
}


/**
 * @brief Rend le QLabel indication visible
 *
 * @return   void
 */
void ChoixVoisinage::afficherMessage()
{
    indication->setVisible(true);
}


/**
 * @brief Colorie les cases de la QTableView visu dont les coordonnees sont passees en argument
 *
 * @param[in] i Coordonnee ligne de la case a colorier
 * @param[in] j Coordonnee colonne de la case a colorier
 * @return   void
 */
void ChoixVoisinage::colorierCase(int i, int j)
{
    visu->item(i,j)->setData(Qt::BackgroundRole,QColor(0,0,0));

}


/**
 * @brief Enregistre le choix du voisinage final : definit l'attribut Voisinage choice afin de le passer en argument au widgent fils
 *
 * @return   void
 */
void ChoixVoisinage::enregistrerChoixVoisinage()
{
    // on récupère les paramètres finalement sélectionnés
    int index = listeVois->currentIndex();
    int rayonChoisi = choixRayon->value();
    quelVoisinage(index, rayonChoisi);

    if (listeVois->currentIndex()==2) // personnalisé : il faut ajouter les cellules à l'ensemble de cases
    {
        std::vector<Case> tableau;
        for (size_t i = 0; i<calculDimSide(); i++)
        {
            for (size_t j=0; j<calculDimSide(); j++)
            {
                if (visu->item(i,j)->background().color() == QColor(0,0,0))
                {
                    tableau.push_back(Case(i-lineMiddleCell, j-collumnMiddleCell));
                }
            }
        }
        if (tableau.empty()) // on affiche un message d'erreur si l'utilisateur n'a selectionne aucune case
        {
            QMessageBox* zeroCases = new QMessageBox;
            zeroCases->setText("Veuillez selectionner au moins une case.");
            zeroCases->show();
        }
        else
        {
            choice->setensemble_case(tableau);
            tableau.clear(); // on libère la mémoire du vecteur
        }
    }

    // on crée une fenetre ChoixEtats pour passer à la prochaine étape de la création du modèle : la définition des états
    ChoixEtats* fenetre_ChoixEtats = new ChoixEtats(this,choice,transition);
    fenetre_ChoixEtats->show();

    this->close();
}


