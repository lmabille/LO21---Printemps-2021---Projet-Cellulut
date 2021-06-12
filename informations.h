#ifndef INFORMATIONS_H
#define INFORMATIONS_H

#include <QDialog>
#include "Modele.h"
#include "menuprincipale_2.h"

namespace Ui {
class informations;
}

class informations : public QDialog
{
    Q_OBJECT

public slots:
    void enregistrerModele();

public:
    explicit informations(QWidget *parent = nullptr, Modele * M=nullptr);
    ~informations();

private:
    Ui::informations *ui;
    Modele * M;
};

#endif // INFORMATIONS_H
