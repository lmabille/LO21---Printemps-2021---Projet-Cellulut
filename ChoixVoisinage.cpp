#include "ChoixVoisinage.h"


size_t ChoixVoisinage::calculRayonMax(size_t nbLignesReseau, size_t nbColonnesReseau)
/* Calcule le rayon max du voisinage que l'on peut afficher en fonction de la taille du reseau */
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

void ChoixVoisinage::calculDimSide (size_t rayonMax)
/* calcule les dimensions max de l'affichage du voisinage en fonction du rayon max */
{
    dimSide = rayonMax*2 + 1;
}


Voisinage* ChoixVoisinage::quelVoisinage(int i)
/* détermine le voisinage à construire en fonction de l'index sélectionné dans la combobox */
{
    switch(i)
    {
    Voisinage* v;
    case 0: // Von Neumann
    {
        std::cout << "\tAOUIOUI " << i << endl;
        V_VonNeumann* vN = new V_VonNeumann();
        vN->definir_ensemble_case(1);
        return vN;
        break;
    }
    case 1: // Moore
    {
        std::cout << "\tAOUIOUI " << i<< endl;
        V_Moore* vM = new V_Moore();
        vM->definir_ensemble_case(1);
        return vM;
        break;
    }
    case 2:
    {
        std::cout << "\tAOUIOUI " << i<< endl;
        V_ChoixUtilisateur* vU = new V_ChoixUtilisateur();
        vU->definir_ensemble_case(1);
        return vU;
        break;
    }
    default:
        return NULL;
    }
}

void ChoixVoisinage::cleanAppercu()
{
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

void ChoixVoisinage::chargerAppercu()
/* affiche l'apperçu du voisinage sélectionné dans la combobox qd l'utilisateur clique sur "Apperçu" */
{
    cleanAppercu();
    // la grille avec seule la case du milieu a été créé grâce au constructeur
    // s'occuper du rayon aussi
    // on récupère le voisinage correspondant à la comboBox
    std::cout << "YOUHOU " << listeVois->currentIndex() << endl;

    Voisinage* voisinageChoisi = quelVoisinage(listeVois->currentIndex());
    std::cout << "yo";

    Case* coordonneesAColorier = voisinageChoisi->getTableau();
    int nombreCases = voisinageChoisi->getNbCelluleVoisi();
    size_t l, c;
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

/*
void ChoixVoisinage::connexionVoisAppercu()
// connecte le bouton "Apperçu" à l'affichage du voisinage
{
    connect(appercu, SIGNAL(clicked()),this,SLOT(chargerAppercu()));
}
*/

ChoixVoisinage::ChoixVoisinage(QWidget* parent, size_t L, size_t C)
/* Constructeur de la classe choix Voisinage : construit la grille de base où les apperçus des voisinages vont être affichés */
{
    // Layout affichage

    // grille de cellules (visu)

    size_t tailleCell = 15;
    size_t rayonMax = calculRayonMax(L,C); // on récupère le rayon maximal en fonction des dimensions du réseau choisies
    calculDimSide(rayonMax); // on recup les dimensions maximales de l'affichage
    calculCoordMiddleCell(); // on calcule les coordonnées de la cellule du milieu

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
    // listeVois->setEditText("Choisir un voisinage");
    listeVois->insertItem(0,"Von Neumann");
    listeVois->insertItem(1,"Moore");
    listeVois->insertItem(2,"Personnalise");

    appercu = new QPushButton("Apperçu");
    connect(appercu, SIGNAL(clicked()),this,SLOT(chargerAppercu()));

    // indication = new QLabel;


    // layout
    parametres = new QHBoxLayout();
    parametres->addWidget(listeVois);
    parametres->addWidget(appercu);


    // Layout final (fenetre)
    fenetre = new QVBoxLayout;

    fenetre->addLayout(parametres);
    fenetre->addLayout(affichage);
    fenetre->addLayout(actions);

    setLayout(fenetre);

}
