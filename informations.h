#ifndef INFORMATIONS_H
#define INFORMATIONS_H

#include <QDialog>
#include "Modele.h"
#include "menuprincipale_2.h"
#include <string.h>

namespace Ui {
class informations;
}

class informations : public QDialog
{
    Q_OBJECT

public slots:
    void enregistrerModele();

public:
    explicit informations(QWidget *parent = nullptr, string nomFctTrans="", Voisinage *V=nullptr, EnsembleEtats * e =nullptr, string typeFcttrans="");
    ~informations();

private:
    Ui::informations *ui;
    string nomFctTrans;
    Voisinage * V;
    EnsembleEtats * e;
    string typeFcttrans;
};

#endif // INFORMATIONS_H
