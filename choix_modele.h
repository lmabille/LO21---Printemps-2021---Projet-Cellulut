#ifndef CHOIX_MODELE_H
#define CHOIX_MODELE_H

#include <QDialog>
#include<QDir>
#include"fenetreconfiguration.h"
#include<QListWidgetItem>
#include "chargerModele.h"
#include <QString>


namespace Ui {
class Choix_Modele;
}

class Choix_Modele : public QDialog
{
    Q_OBJECT

public slots:
    void recupModele(QListWidgetItem*);

public:
    explicit Choix_Modele(QWidget *parent = nullptr);
    ~Choix_Modele();

private:
    Ui::Choix_Modele *ui;
};

#endif // CHOIX_MODELE_H
