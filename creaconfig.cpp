#include "creaconfig.h"
#include "ui_creaconfig.h"

QTextStream& qStdOut();

CreaConfig::CreaConfig(QWidget *parent, Simulateur * simu) :
    QDialog(parent),
    ui(new Ui::CreaConfig),
    simu(simu)
{





    ui->setupUi(this);

    //ui->LayoutGrille->addWidget(grille);




}

CreaConfig::~CreaConfig()
{
    delete ui;
}

void CreaConfig::on_btnTaille_clicked()
{
    cout<<"salut";
    //stoi("2");
    int ligne,colonne;
    ligne = ui->spinLigne->value();
    colonne = ui->spinColonne->value();
    this->res = new Reseau(ligne,colonne);

    Configuration * config = new Configuration(*res);
    /*qStdOut() << QString::fromStdString(simu->getModele()->getEtatsPossibles()->getListe()[0].getLabel() + " " );
    qStdOut() << QString::number(simu->getModele()->getEtatsPossibles()->getListe()[0].getIndice())<< " ";

    qStdOut() << QString::fromStdString(simu->getModele()->getEtatsPossibles()->getListe()[1].getLabel() + " " );



    qStdOut() << QString::number(simu->getModele()->getEtatsPossibles()->getListe()[0].getIndice());*/

    for (int i = 0; i< ligne; i ++){
        for (int j = 0; j < colonne ; j++) {
            config->setEtatCellule(i,j,&simu->getModele()->getEtatsPossibles()->getListe()[0]);
        }
    }

    config_cour = config;

    this->simu->setConfigDepart(*config);
    cout << "config creer";

    chargerGrille();

}

void CreaConfig::chargerGrille() {
    //unsigned int taille = 20;//taille cellule

    const int nbLigne= this->simu->getConfigurationDepart()->getReseauLignes();
    const int nbColonne= this->simu->getConfigurationDepart()->getReseauColonnes();
    // unsigned int nbLigne=15;
   //unsigned int nbColonne=20;

    /*
    QTableWidget * grille = new QTableWidget(nbLigne, nbColonne);//ici on met la taille passé en argument
    grille->setFixedSize(2.61*taille*nbColonne, 1.61*taille*nbLigne);//permet d'agrandir la fenetre en faire une fonction de la taille

    //QLabel * test = new QLabel(QString::number(nbLigne));
    //ui->LayoutGrille->addWidget(test);

    //On enlève les labels et les scrollbar
    grille->horizontalHeader()->setVisible(false);
    grille->verticalHeader()->setVisible(false);
    //grille->verticalHeader().hide();
    grille->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    grille->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i=0; i<nbLigne; i++ ){//pour chaque colonne
        for(int j=0; j<nbColonne; j++){//pour chaque ligne
            grille->setColumnWidth(j, taille);
            grille->setRowHeight(i, taille);
            grille->setItem(i, j, new QTableWidgetItem(""));
            //On récupère la couleur de l'état
            //string couleur = "noir";
            string couleur = this->simu->getConfigurationDepart()->getEtatCellule (i, j).getCouleur();/*
            if(couleur == "noir")grille->item(i, j)->setData(Qt::BackgroundRole, QColor(0, 0, 0));
            if(couleur == "blanc")grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 255, 255));
           // grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 0, 255));
        }
    }*/


        //QWidget * container = new QWidget;

        QGridLayout * grid = new QGridLayout(this);

        grid->maximumSize().setHeight(300);
        grid->maximumSize().setWidth(300);
        grid->setContentsMargins(0,0,0,0);
        grid->setSpacing(0);
        //grid.set

        //Configuration* config = this->simu->getConfigurationDepart();
        for(int i = 0; i < nbColonne; i++)
        {
            for(int j = 0; j < nbLigne; j++)
            {
                QPushButton * button = new QPushButton();
                button->setFixedSize(30,30);
                grid->addWidget(button, j, i);

                // Set size text etc. for each button
                button->setText(QString::number(simu->getConfigurationDepart()->getEtatCellule(j,i).getIndice()));

                cout << simu->getConfigurationDepart()->getEtatCellule(j,i).getCouleur()  <<endl;// " " << i<< " " <<j <<endl ;
                string couleur = simu->getConfigurationDepart()->getEtatCellule(j,i).getCouleur();
                //string couleur = config->getEtatCellule (i, j).getCouleur();
                if(couleur == "noir")button->setStyleSheet("background-color : rgb(0, 0, 0)");
                if(couleur == "blanc")button->setStyleSheet("background-color : rgb(255, 255, 255)"); // (255, 255, 255));
                if(couleur == "rouge")button->setStyleSheet("background-color : rgb(255, 0, 0)");//(255, 0, 0));
                if(couleur == "vert")button->setStyleSheet("background-color : rgb(50, 255, 0)"); //(50, 255, 0));
                if(couleur == "bleu")button->setStyleSheet("background-color : rgb(0, 0, 255)"); //(0, 0, 255));
                if(couleur == "jaune")button->setStyleSheet("background-color : rgb(255, 215, 50)"); //(255, 215, 50));
                if(couleur == "magenta")button->setStyleSheet("background-color : rgb(255, 0, 255)"); // (255, 0, 255));
                if(couleur == "rose")button->setStyleSheet("background-color : rgb(255, 150, 203)"); //(255, 150, 203));
                if(couleur == "orange")button->setStyleSheet("background-color : rgb(255, 130, 20)");// (255, 130, 20));
                if(couleur == "peppermint")button->setStyleSheet("background-color : rgb(148, 255, 216)"); //(187, 254, 190));


                //button->setStyleSheet("background-color : rgb(148, 255, 216)");
                connect(button, &QPushButton::clicked, [=](){
                    //func(i, j);     // Call the function which uses i and j here
                    changeEtat(i,j,this->config_cour,button);
                });
            }

       /*

    QLayoutItem *item;
        while ((item = ui->LayoutGrille->takeAt(0)))
        {
            /*if (item->layout())
            {
                clearLayout(item->layout());
            }*

            ui->LayoutGrille -> removeItem(item);
            delete item;
        }*/

    //clearLayout(ui->LayoutGrille);
    //ui->LayoutGrille = new QVBoxLayout();
           //ui->LayoutGrille->setLayout(nullptr);

    ui->LayoutGrille->setLayout(grid);
}


}

void CreaConfig::clearLayout(QLayout* layout) {
    QLayoutItem *item;
        while ((item = layout->takeAt(0)))
        {
            if (item->layout())
            {
                clearLayout(item->layout());
            }

            layout -> removeItem(item);
            delete item;
        }
}


void CreaConfig::changeEtat(int j,int i,Configuration* config, QPushButton* button) {
    int indice = config->getEtatCellule(i,j).getIndice();
    //qStdOut() << QString::number(indice);

    cout <<"nb etat" <<simu->getModele()->getEtatsPossibles()->getNombreEtats() <<endl;
    cout <<"L:" <<simu->getModele()->getEtatsPossibles()->getListe()[indice].getLabel() << " I:"<< simu->getModele()->getEtatsPossibles()->getListe()[indice].getIndice() << " C:"<< simu->getModele()->getEtatsPossibles()->getListe()[indice].getCouleur() << endl;

    cout <<"Avant L:" <<config->getEtatCellule(i,j).getLabel() << " I:"<< config->getEtatCellule(i,j).getIndice() << " C:"<< config->getEtatCellule(i,j).getCouleur() << endl;

    if (indice == simu->getModele()->getEtatsPossibles()->getNombreEtats()-1)
        indice = 0;
    else
        indice +=1;
    config->setEtatCellule(i,j,&simu->getModele()->getEtatsPossibles()->getListe()[indice]);
    cout <<"Après L:" <<config->getEtatCellule(i,j).getLabel() << " I:"<< config->getEtatCellule(i,j).getIndice() << " C:"<< config->getEtatCellule(i,j).getCouleur() << endl;



    string couleur = config->getEtatCellule (i, j).getCouleur();
    if(couleur == "noir")button->setStyleSheet("background-color : rgb(0, 0, 0)");
    if(couleur == "blanc")button->setStyleSheet("background-color : rgb(255, 255, 255)");// (255, 255, 255));
    if(couleur == "rouge")button->setStyleSheet("background-color : rgb(255, 0, 0)");//(255, 0, 0));
    if(couleur == "vert")button->setStyleSheet("background-color : rgb(50, 255, 0)"); //(50, 255, 0));
    if(couleur == "bleu")button->setStyleSheet("background-color : rgb(0, 0, 255)"); //(0, 0, 255));
    if(couleur == "jaune")button->setStyleSheet("background-color : rgb(255, 215, 50)"); //(255, 215, 50));
    if(couleur == "magenta")button->setStyleSheet("background-color : rgb(255, 0, 255)"); // (255, 0, 255));
    if(couleur == "rose")button->setStyleSheet("background-color : rgb(255, 150, 203)"); //(255, 150, 203));
    if(couleur == "orange")button->setStyleSheet("background-color : rgb(255, 130, 20)");// (255, 130, 20));
    if(couleur == "peppermint")button->setStyleSheet("background-color : rgb(148, 255, 216)"); //(187, 254, 190));







    /*

    if (indice == 1)
        button->setStyleSheet("background-color : rgb(148, 255, 216)");
    else
        button->setStyleSheet("background-color : white");*/
    button->setText(QString::number(indice));

    qStdOut() << "test" ;
    qStdOut() << QString::fromStdString(config->getCellule(i,j).get_Etat().getLabel());

    this->simu->setConfigDepart(*config);

}


QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}



void CreaConfig::on_btnRandom_clicked()
{
    this->simu->getConfigurationDepart()->remplissageAleatoire(*this->simu->getModele()->getEtatsPossibles());

    //ui->LayoutGrille->childAt(0,0)->childAt(0,0)->setStyleSheet("background-color : rgb(255, 0, 0)");
    /*
    for (int i = 0; i < this->simu->getConfigurationDepart()->getReseauColonnes(); i++) {
        for (int j = 0 ; j < this->simu->getConfigurationDepart()->getReseauLignes(); j ++) {
            QLayoutItem * item = ui->LayoutGrille->children()
        }
    }*/



}
