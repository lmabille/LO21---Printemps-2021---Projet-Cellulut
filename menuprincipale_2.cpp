#include "menuprincipale_2.h"
#include "ui_menuprincipale_2.h"

MenuPrincipale_2::MenuPrincipale_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuPrincipale_2)
{
    ui->setupUi(this);
}

MenuPrincipale_2::~MenuPrincipale_2()
{
    delete ui;
}

void MenuPrincipale_2::afficherModeles()
{
    Choix_Modele * Menu = new Choix_Modele;
    Menu->show();
    this->close();
}
/*
void MenuPrincipale_2::afficher_taille_reseaux(){
    taille_reseau * TR = new taille_reseau;
    TR->show();
    this->close();
};*/

void MenuPrincipale_2::afficher_choix_transition(){
    choixTransition * ct = new choixTransition;
    ct->show();
    this->close();
};
