#ifndef MENUPRINCIPALE_2_H
#define MENUPRINCIPALE_2_H

#include <QDialog>
#include "choix_modele.h"
#include "taille_reseau.h"
#include "choixTransition.h"

namespace Ui {
class MenuPrincipale_2;
}

class MenuPrincipale_2 : public QDialog
{
    Q_OBJECT

public:
    explicit MenuPrincipale_2(QWidget *parent = nullptr);
    ~MenuPrincipale_2();

public slots:
    void afficherModeles();
    //void afficher_taille_reseaux();
    void afficher_choix_transition();

private:
    Ui::MenuPrincipale_2 *ui;
};

#endif // MENUPRINCIPALE_2_H
