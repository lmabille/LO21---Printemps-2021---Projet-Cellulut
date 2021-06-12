#include "informations.h"
#include "ui_informations.h"

informations::informations(QWidget *parent , string nomFctTrans, Voisinage *V, EnsembleEtats * e, string typeFcttrans) :
    QDialog(parent),
    ui(new Ui::informations),
    nomFctTrans(nomFctTrans),
    V(V),
    e(e),
    typeFcttrans(typeFcttrans)
{
    ui->setupUi(this);
}

informations::~informations()
{
    delete ui;
}

void informations::enregistrerModele(){
    //enregistrement des infos manquantes du modèle
    string *tab;
    int nbregle=0;
    int nbVoisin = V->getNbCelluleVoisi();

    //génération des règles correspondant à la bonne fonction de transition
    if (std::strcmp(nomFctTrans.c_str(), "Life's_game") == 0) tab = generation_regles_Life_game(nbVoisin,nbregle);
    else if(std::strcmp(nomFctTrans.c_str(), "WireWorld") == 0) tab = generation_regles_Wireworld(nbVoisin, nbregle);
    else if(std::strcmp(nomFctTrans.c_str(), "Langston Loop") == 0) tab = generation_regles_Langton_Loop(nbregle);
    else if(std::strcmp(nomFctTrans.c_str(), "Griffeath") == 0) tab = generation_regles_Griffeath(nbVoisin, nbregle);
    else if(std::strcmp(nomFctTrans.c_str(), "Brians Brain") == 0) tab = generation_regles_Brians_Brain(nbVoisin, nbregle);

    FonctionTransition * f ;

    if(std::strcmp(typeFcttrans.c_str(), "extention") == 0) f = new FonctionTransition(tab, nbregle);
    else f = new FonctionTransitionIntention(tab, nbregle);

    auto m = new Modele("modele 1",e, f,typeFcttrans, V, (this->ui->textEdit->toPlainText()).toStdString(), (this->ui->lineEdit_2->text()).toStdString(), (this->ui->lineEdit->text()).toInt());

    m->sauvegardeM();//sauvegarde du modèle

    auto Menu = new MenuPrincipale_2;

    Menu->show();//on réouvre le menu principal

    this->close();//et enfin on ferme la page


}
