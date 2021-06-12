#include "informations.h"
#include "ui_informations.h"

informations::informations(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::informations)
{
    ui->setupUi(this);
}

informations::~informations()
{
    delete ui;
}

void informations::enregistrerModele(){
    //enregistrement des infos manquantes du modèle
    this->M->setAnnee((this->ui->lineEdit->text()).toInt());
    this->M->setAutheur((this->ui->lineEdit_2->text()).toStdString());
    this->M->setDesc((this->ui->textEdit->toPlainText()).toStdString());

    M->sauvegardeM();//sauvegarde du modèle

    auto Menu = new MenuPrincipale_2;

    Menu->show();//on réouvre le menu principal

    this->close();//et enfin on ferme la page


}
