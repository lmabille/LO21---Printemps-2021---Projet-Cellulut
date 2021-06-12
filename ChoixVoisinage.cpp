#include "ChoixVoisinage.h"


// CONSTRUCTEUR

ChoixVoisinage::ChoixVoisinage(QWidget* parent, size_t L, size_t C)
/* Constructeur de la classe choix Voisinage : construit la grille de base où les apperçus des voisinages vont être affichés */
{
    // GRILLE

    size_t tailleCell = 15; // taille cellule

    setRayonMax(L,C); // calcul rayon

    std::cout << "rayon de " << rayonMax << " OK " << endl;

    calculCoordMiddleCell(); // calcul des coordonnées de la cellule du milieu

    size_t dimSide = calculDimSide(rayonMax); // on recup les dimensions maximales de l'affichage
    std::cout << "dimSide = " << dimSide << endl;

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
    indication->setText("Veuillez rechargez l'aperçu");
    indication->setVisible(false);

    // choix du rayon (choixRayon)
    choixRayon = new QSpinBox();
    choixRayon->setRange(1,rayonMax);
    choixRayon->setVisible(false);
    connect(choixRayon, SIGNAL(valueChanged(int)),this,SLOT(chargerAppercu()));
    //connect(choixRayon, SIGNAL(valueChanged(int)),this,SLOT(afficherMessage()));

    // layout
    affichage = new QHBoxLayout;
    affichage->addWidget(visu);
    affichage->addWidget(choixRayon);
    affichage->addWidget(indication);


    // PARAMETRES

    listeVois = new QComboBox();
    // listeVois->setEditText("Choisir un voisinage");

    // les voisinages possibles dépendent de la fonction de transition qui a été choisie
    if (transition.compare("Langton's Loop")==0)
    {
        std::cout << "langstonloop bro" << endl;
        listeVois->insertItem(0,"Von Neumann");
        choixRayon->setMaximum(1);
    }
    else
    {
        std::cout << "pas langston loop BRO" << endl;
        listeVois->insertItem(0,"Von Neumann");
        listeVois->insertItem(1,"Moore");
        listeVois->insertItem(2,"Personnalise");
    }

    connect(listeVois, SIGNAL(currentIndexChanged(int)),this, SLOT(indexChanged(int)));

    // layout
    parametres = new QHBoxLayout();
    parametres->addWidget(listeVois);


    // ACTIONS

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


// CALCUL RAYON MAX DU VOISINAGE

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


// CALCUL DIMENSION DE L'APPERCU EN FONCTION DU RAYON

size_t ChoixVoisinage::calculDimSide (size_t rayonMax)
/* calcule les dimensions max de l'affichage du voisinage en fonction du rayon max */
{
    size_t dimSide = rayonMax*2 + 1;
    return dimSide;
}


// REMET TOUTES LES CASES NOIRES DE L'APPERCU A BLANC (pas la cellule du milieu rouge donc)

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


// AFFICHE L'APPERCU EN FONCTION DU VOISINAGE SELECTIONNE

void ChoixVoisinage::chargerAppercu()
/* affiche l'apperçu du voisinage sélectionné dans la combobox (VNeum ou Moore de rayons variables) qd l'utilisateur clique sur "Apperçu" */
{
    cleanAppercu(); // on remet l'apperçu à blanc

    int index = listeVois->currentIndex();

    if (index==0 || index==1) // on affiche le rayon si vneum ou moore
    {
        std::cout << "ON VA CHARGER UN APPERCU VN OU MOOOORE" << endl;
        choixRayon->setVisible(true);
    }
    else std::cout << "ON VA CHARGER UN APPERCU PERSOOOOOOOO" << endl;

    int rayonChoisi = choixRayon->value();
    quelVoisinage(index, rayonChoisi); // on crée l'objet voisinage en fonction du choix de l'utilisateur

    if (index==0 || index==1) // moore ou von neuman
    {
    // on colorie les cases en fonction du tableau rempli
        Case* coordonneesAColorier = choice->getTableau();
        int nombreCases = choice->getNbCelluleVoisi();

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
    else
    {
        // on demande à l'utilisateur de choisir ses cases
        indication->setText("Cliquez sur les voisines");
        afficherMessage();

        choixRayon->setVisible(false);
        connect(visu, SIGNAL(cellClicked(int,int)), this, SLOT(colorierCase(int,int))); // toutes les cases choisies deviennent noires
    }

    // choice->~Voisinage(); // on détruit le voisinage REDEFINIR LES DESTRUCTEURS
    delete choice;
    choice = nullptr;
    if (choice==nullptr) std::cout<< "voisinage bien detruit" <<endl; // heu marche pas??
}


// CREE UN VOISINAGE SELON LE CHOIX DE L'UTILISATEUR POUR RECUPERER SES CASES

void ChoixVoisinage::quelVoisinage(int i, size_t rayon)
/* détermine le voisinage à construire en fonction de l'index sélectionné dans la combobox */
{
    switch(i)
    {
    case 0: // Von Neumann
    {
        std::cout << "\tAOUIOUI " << i << endl;
        V_VonNeumann* vN = new V_VonNeumann();
        vN->definir_ensemble_case(rayon);
        choice = static_cast <V_VonNeumann*> (vN);
        break;
    }
    case 1: // Moore
    {
        std::cout << "\tAOUIOUI " << i<< endl;
        V_Moore* vM = new V_Moore();
        vM->definir_ensemble_case(rayon);
        choice = static_cast <V_Moore*> (vM);
        break;
    }
    case 2:
    {
        std::cout << "\tAOUIOUI " << i<< endl;
        V_ChoixUtilisateur* vU = new V_ChoixUtilisateur();
        vU->definir_ensemble_case(rayon);
        choice = static_cast <V_ChoixUtilisateur*> (vU);
        break;
    }
    }
}


// AFFICHE UNE INDICATION A L'UTILISATEUR

void ChoixVoisinage::afficherMessage()
{
    indication->setVisible(true);
}


// COLORIE LES CASES ET SET L'ENSEMBLE DE CASE DU VOISINAGE PERSONNALISE

void ChoixVoisinage::colorierCase(int i, int j)
{
    visu->item(i,j)->setData(Qt::BackgroundRole,QColor(0,0,0));

}


// VALIDATION DU CHOIX

void ChoixVoisinage::enregistrerChoixVoisinage()
{
    std::cout << "askip ca enregistre hehe" <<endl;

    // on récupère les paramètres finalement sélectionnés
    int index = listeVois->currentIndex();
    int rayonChoisi = choixRayon->value();
    quelVoisinage(index, rayonChoisi);

    std::cout<<"bien recu chef"<<endl;

    if (listeVois->currentIndex()==2) // personnalisé : il faut ajouter les cellules à l'ensemble de cases
    {
        std::cout << "PERSO ? PASDESOUC " <<endl;

        std::vector<Case> tableau;
        for (size_t i = 0; i<calculDimSide(rayonMax); i++)
        {
            for (size_t j=0; j<calculDimSide(rayonMax); j++)
            {
                if (visu->item(i,j)->background().color() == QColor(0,0,0))
                {
                    tableau.push_back(Case(i-lineMiddleCell, j-collumnMiddleCell));
                    //std::cout << tableau.end()->getL() << "," << tableau.end()->getC();
                }
            }
        }
        if (tableau.empty())
        {
            std::cout << "vide sa mere" <<endl;
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

    std::cout << "VOILOU TABOM" <<endl;
    std::cout << "cest un voisinage " << choice->getTypeVoisi() <<endl;
    Case* tab = choice->getTableau();
    for (size_t i=0;i<choice->getNbCelluleVoisi();i++)
    {
        std::cout << "yooo" <<endl;
        std::cout << tab[i].getL() <<","<<tab[i].getC() <<endl;
    }

    // envoyer le voisinage et la fonction de transition à la widget etats de laurine
    ChoixEtats* fenetre_ChoixEtats = new ChoixEtats(this,choice,transition);
    fenetre_ChoixEtats->show();
}


