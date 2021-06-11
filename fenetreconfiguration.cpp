#include "fenetreconfiguration.h"
#include "ui_fenetreconfiguration.h"

FenetreConfiguration::FenetreConfiguration(QWidget *parent, Modele * modele, Simulateur* simul, const char * nom ) :
    QDialog(parent),

    ui(new Ui::FenetreConfiguration),
    nom_fichier(nom),
    simul(simul),
    modele(modele)
{
    int nb = getNbConfig(this->nom_fichier);
    string * liste_config = new string[nb]();
    liste_config = getListeConfig(this->nom_fichier);



    //ui->comboBox->addItem(QString::fromStdString(liste_config[0]));
    //QLabel * test = new QLabel(this);
    //test->setText("test");


    cout<<"passe1";

    ui->setupUi(this);
    //ui->comboBox->addItem(QString::fromStdString(liste_config[0]));
    remplirComboList(liste_config,nb);
    initConnect(this->simul);

    //chargerPreview();
}

FenetreConfiguration::~FenetreConfiguration()
{
    delete ui;
}

void FenetreConfiguration::remplirComboList(string * liste,int nb) {
    for (int i =0; i<nb; i++) {
        ui->comboBox->addItem(QString::fromStdString(liste[i]));
    }
}
void FenetreConfiguration::chargerConfig() {
    string nom =  ui->comboBox->currentText().toStdString();
    Configuration * config = chargerConfiguration(this->nom_fichier,nom);
    this->simul->setConfigDepart(*config);
    ui->label->setText(QString::fromStdString(nom));
    ui->label->show();
}


void FenetreConfiguration::initConnect(Simulateur* simul) {
    connect(ui->btnCharger,SIGNAL(pressed()),this,SLOT(on_btnCharger_clicked()));
}



void FenetreConfiguration::on_btnCharger_clicked()
{
    //ui->label->setText("test");
    //ui->label->show();
    chargerConfig();
    chargerPreview();


}

void FenetreConfiguration::chargerPreview() {
    unsigned int taille = 5;//taille cellule

    const int nbLigne= this->simul->getConfigurationDepart()->getReseauLignes();
    const int nbColonne= this->simul->getConfigurationDepart()->getReseauColonnes();
    // unsigned int nbLigne=15;
   //unsigned int nbColonne=20;
    QTableWidget * grille = new QTableWidget(nbLigne, nbColonne);//ici on met la taille passé en argument
    grille->setFixedSize(400,300);//permet d'agrandir la fenetre en faire une fonction de la taille

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
            int indice = this->simul->getConfigurationDepart()->getEtatCellule (i, j).getIndice();
            if(indice == 0)grille->item(i, j)->setData(Qt::BackgroundRole, QColor(0, 0, 0));
            if(indice == 1)grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 255, 255));

           // grille->item(i, j)->setData(Qt::BackgroundRole, QColor(255, 0, 255));
        }
    }

    QLayoutItem *item;
        while ((item = ui->LayoutPreview->takeAt(0)))
        {
            /*if (item->layout())
            {
                clearLayout(item->layout());
            }*/

            ui->LayoutPreview -> removeItem(item);
            delete item;
        }



    //ui->LayoutPreview->removeWidget(ui->LayoutPreview->widget());
    //delete ui->LayoutPreview->widget();
    ui->LayoutPreview->addWidget(grille);
    //ui->FramePreview->add
    //ui->FramePreview->addWidget(grille);


}

void FenetreConfiguration::creerConfig() {
    CreaConfig * pageConfig = new CreaConfig(this,simul);
    pageConfig->show();

}

void FenetreConfiguration::on_btnCreer_clicked()
{
    creerConfig();
}

void FenetreConfiguration::on_btnReload_clicked()
{
    chargerPreview();
}

void FenetreConfiguration::on_btnValider_clicked()
{
    qSimulateur* fenetre = new qSimulateur(nullptr, modele, simul->getConfigurationDepart());


    fenetre->show();
}
