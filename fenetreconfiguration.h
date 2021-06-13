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
#include "qSimulateur.h"

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

    void on_btnCreer_clicked();

    void on_btnReload_clicked();

    void on_btnValider_clicked();

private:
    Ui::FenetreConfiguration *ui;
    const char* nom_fichier;
    Modele * modele;
    void remplirComboList(string * liste, int nb);
    void initConnect();
    void chargerConfig();
    Simulateur * simul;
    void chargerPreview();
    void creerConfig();
};

#endif // FENETRECONFIGURATION_H
