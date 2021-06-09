#include "ChoixVoisinage.h"




size_t ChoixVoisinage::calculRayonMax(size_t nbLignesReseau, size_t nbColonnesReseau)
/* Calcule les dimensions max du voisinage que l'on peut afficher en fonction de la taille du reseau */
{
    size_t rayonMax = 0;
    size_t actualSide = min(nbLignesReseau, nbColonnesReseau);
    if (actualSide%2 == 1) // impair
    {
        rayonMax = actualSide/2; // actualSide est un entier donc renvoie une division entière
    }
    else
    {
        rayonMax = (actualSide - 1)/2;
    }
    return rayonMax;
}

size_t ChoixVoisinage::calculDimSide (size_t rayonMax)
{
    return rayonMax*2 + 1;
}

ChoixVoisinage::ChoixVoisinage(QWidget* parent, size_t L, size_t C)
{
    // Layout affichage

    // grille de cellules (visu)

    size_t tailleCell = 15;
    size_t rayonMax = calculRayonMax(L,C); // on récupère le rayon maximal en fonction des dimensions du réseau choisies
    const size_t dimSide = calculDimSide(rayonMax); // on recup les dimensions maximales de l'affichage

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
            if (i==dimSide/2 && j==dimSide/2) visu->item(i,j)->setData(Qt::BackgroundRole, QColor(0,0,0)); // cellule du centre
            else visu->item(i,j)->setData(Qt::BackgroundRole, QColor(255,255,255)); // à la création, toutes les cellules sont blanches sauf celle du centre
        }
    }

    // choix du rayon (choixRayon)

    choixRayon = new QSpinBox();
    choixRayon->setRange(1,rayonMax);

    // Layout
    affichage = new QHBoxLayout;
    affichage->addWidget(visu);
    affichage->addWidget(choixRayon);


    // Layout actions

    retour = new QPushButton("Retour");
    validation = new QPushButton("Valider");

    // Layout
    actions = new QHBoxLayout;
    actions->addWidget(retour);
    actions->addWidget(validation);


    // Layout parametres

    listeVois = new QComboBox();
    listeVois->setEditText("Choisir un voisinage"); // wtf
    listeVois->addItem("Von Neumann");
    listeVois->addItem("Moore");
    listeVois->addItem("Creer mon propre voisinage");

    indication = new QLabel;


    // layout
    parametres = new QVBoxLayout();
    parametres->addWidget(listeVois);


    // Layout final (fenetre)
    fenetre = new QVBoxLayout;

    fenetre->addLayout(parametres);
    fenetre->addLayout(affichage);
    fenetre->addLayout(actions);

    setLayout(fenetre);


}
