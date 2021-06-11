#include "ChoixVoisinage.h"


void ChoixVoisinage::setRayonMax(size_t nbLignesReseau, size_t nbColonnesReseau)
/* Calcule le rayon max du voisinage que l'on peut afficher en fonction de la taille du reseau */
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
    std::cout << "LE RAYON EST DE " << rayonMax << endl;
}

size_t ChoixVoisinage::calculDimSide (size_t rayonMax)
/* calcule les dimensions max de l'affichage du voisinage en fonction du rayon max */
{
    size_t dimSide = rayonMax*2 + 1;
    return dimSide;
}


Voisinage* ChoixVoisinage::quelVoisinage(int i, size_t rayon)
/* détermine le voisinage à construire en fonction de l'index sélectionné dans la combobox */
{
    switch(i)
    {
    case 0: // Von Neumann
    {
        std::cout << "\tAOUIOUI " << i << endl;
        V_VonNeumann* vN = new V_VonNeumann();
        vN->definir_ensemble_case(rayon);
        return vN;
        break;
    }
    case 1: // Moore
    {
        std::cout << "\tAOUIOUI " << i<< endl;
        V_Moore* vM = new V_Moore();
        vM->definir_ensemble_case(rayon);
        return vM;
        break;
    }
    case 2:
    {
        std::cout << "\tAOUIOUI " << i<< endl;
        V_ChoixUtilisateur* vU = new V_ChoixUtilisateur();
        vU->definir_ensemble_case(rayon);
        return vU;
        break;
    }
    default:
        return NULL;
    }
}


void ChoixVoisinage::cleanAppercu()
{
    size_t dimSide = calculDimSide(rayonMax);
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

void ChoixVoisinage::afficherMessage()
{
    indication->setVisible(true);
}

void ChoixVoisinage::colorierCase(int i, int j)
{
    std::cout<<"on y est mais ***" << endl;
    visu->item(i,j)->setData(Qt::BackgroundRole,QColor(0,0,0));
}

void ChoixVoisinage::chargerAppercu()
/* affiche l'apperçu du voisinage sélectionné dans la combobox (VNeum ou Moore de rayons variables) qd l'utilisateur clique sur "Apperçu" */
{
    cleanAppercu();

    // la grille avec seule la case du milieu a été créé grâce au constructeur

    int indexChoisi = listeVois->currentIndex();

    if (indexChoisi==0 || indexChoisi==1) // VNeum ou Moore
    {
        choixRayon->setVisible(true);
        int rayonChoisi = choixRayon->value();
        std::cout << "rayon choisi = " << rayonChoisi <<endl;

        std::cout << "YOUHOU " << listeVois->currentIndex() << endl;

        Voisinage* voisinageChoisi = quelVoisinage(indexChoisi, rayonChoisi);

        std::cout << "yo";

        Case* coordonneesAColorier = voisinageChoisi->getTableau();
        int nombreCases = voisinageChoisi->getNbCelluleVoisi();
        size_t l, c;
        size_t dimSide = calculDimSide(rayonMax);
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
    else // personnalisé
    {
        std::cout<<"\nca personnalise ici ou quoi" <<endl;
        choixRayon->setVisible(false);
        connect(visu, SIGNAL(cellClicked(int,int)), this, SLOT(colorierCase(int,int)));
    }
}


void ChoixVoisinage::creaGridShowOnly(size_t dimSide, size_t tailleCell)
{
    // Layout affichage
    // grille de cellules (visu)

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
    // choixRayon->setVisible(false);
    connect(choixRayon, SIGNAL(valueChanged(int)),this,SLOT(afficherMessage()));

    // Message recharge
    indication = new QLabel("Veuillez recharger l'apperçu");
    indication->setVisible(false);

    // Layout
    affichage->addWidget(visu);
    affichage->addWidget(choixRayon);
    affichage->addWidget(indication);
}

/*
void colorerCase(QPushButton* button)
{
    button->setStyleSheet("background-color : black");
}

void ChoixVoisinage::creaGridButton(size_t dimSide, size_t tailleCell)
{
    visu->setVisible(false);
    choixRayon->setVisible(false);
    indication->setText("Selectionner les cases");
    QGridLayout* grid = new QGridLayout(this);
    for(size_t i = 0; i < dimSide; i++)
    {
       for(size_t j = 0; j < dimSide; j++)
       {
           QPushButton * button = new QPushButton();
           button->setFixedSize(tailleCell, tailleCell);
           grid->addWidget(button, i, j);
           connect(appercu, SIGNAL(clicked()),this,SLOT(colorerCase(button)));
       }
    }
    affichage->addLayout(grid);
}
*/

void ChoixVoisinage::enregistrerChoixVoisinage()
{
   /* size_t finalRayon = choixRayon->value();

    switch(listeVois->currentIndex())
    {
    case 0: // vonNeum
    {
        finalChoice = new V_VonNeumann();
        finalChoice->definir_ensemble_case(finalRayon);
        break;
    }
    case 1: // Moore
    {
        finalChoice = new V_Moore();
        finalChoice->definir_ensemble_case(finalRayon);
        break;
    }
    case 3: // perso
    {
        finalChoice = dynamic_cast<V_ChoixUtilisateur*> (finalChoice);
        for (size_t i=0; i<calculDimSide(rayonMax); i++)
        {
            for (size_t j=0; j<calculDimSide(rayonMax); j++)
            {
                //if (visu->item(i,j)->background().color() == QColor(0,0,0))
                    //finalChoice->;
            }
        }*/

    }


ChoixVoisinage::ChoixVoisinage(QWidget* parent, size_t L, size_t C)
/* Constructeur de la classe choix Voisinage : construit la grille de base où les apperçus des voisinages vont être affichés */
{
    // Layout parametres

    listeVois = new QComboBox();
    // listeVois->setEditText("Choisir un voisinage");
    listeVois->insertItem(0,"Von Neumann");
    listeVois->insertItem(1,"Moore");
    listeVois->insertItem(2,"Personnalise");

    appercu = new QPushButton("Apperçu");
    connect(appercu, SIGNAL(clicked()),this,SLOT(chargerAppercu()));

    // layout
    parametres = new QHBoxLayout();
    parametres->addWidget(listeVois);
    parametres->addWidget(appercu);

    // grille

    size_t tailleCell = 15;
    setRayonMax(L,C);
    std::cout << "rayon de " << rayonMax << " OK " << endl;

    size_t dimSide = calculDimSide(rayonMax); // on recup les dimensions maximales de l'affichage
    std::cout << "dimSide = " << dimSide << endl;

    affichage = new QHBoxLayout;

    std::cout << "\tOEOE TOUTDEF D'INDICE " << listeVois->currentIndex();
    creaGridShowOnly(dimSide, tailleCell);

    /*
    else // choix Perso
    {
        std::cout << "\tOEOE LE PERSO D'INDICE " << listeVois->currentIndex();
        creaGridButton(dimSide, tailleCell);
    }*/

    // Layout actions

    retour = new QPushButton("Retour");
    validation = new QPushButton("Valider");
    connect(validation,SIGNAL(clicked()),this,SLOT(enregistrerChoixVoisinage()));

    // Layout
    actions = new QHBoxLayout;
    actions->addWidget(retour);
    actions->addWidget(validation);

    // Layout final (fenetre)
    fenetre = new QVBoxLayout;

    fenetre->addLayout(parametres);
    fenetre->addLayout(affichage);
    fenetre->addLayout(actions);

    setLayout(fenetre);

}
