#include "fenetreconfiguration.h"
#include "ui_fenetreconfiguration.h"

FenetreConfiguration::FenetreConfiguration(QWidget *parent, Modele * modele, Simulateur* simul, const char * nom ) :
    QDialog(parent),

    ui(new Ui::FenetreConfiguration),
    nom_fichier(nom),
    simul(simul)
{
    int nb = getNbConfig(this->nom_fichier);
    string * liste_config = new string[nb]();

    liste_config = getListeConfig(this->nom_fichier);



    //ui->comboBox->addItem(QString::fromStdString(liste_config[0]));
    //QLabel * test = new QLabel(this);
    //test->setText("test");





    ui->setupUi(this);
    //ui->comboBox->addItem(QString::fromStdString(liste_config[0]));
    remplirComboList(liste_config,nb);
    initConnect(this->simul);
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
    ui->label->setText("test");
    ui->label->show();
    chargerConfig();

}
