#ifndef FENETRECONFIGURATION_H
#define FENETRECONFIGURATION_H

#include <QDialog>
#include "Modele.h"
#include <QString>
#include "loadConfig.h"
#include "simulateur.h"
#include <QTableWidget>
#include <QHeaderView>
#include "creaconfig.h"

namespace Ui {
class FenetreConfiguration;
}

class FenetreConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit FenetreConfiguration(QWidget *parent = nullptr, Modele * modele = nullptr,Simulateur* simulateur = nullptr, const char* nom_fichier = nullptr);
    ~FenetreConfiguration();

private slots:


    void on_btnCharger_clicked();

private:
    Ui::FenetreConfiguration *ui;
    const char* nom_fichier;
    void remplirComboList(string * liste, int nb);
    void initConnect(Simulateur* simul);
    void chargerConfig();
    Simulateur * simul;
    void chargerPreview();
    void creerConfig();
};

#endif // FENETRECONFIGURATION_H
