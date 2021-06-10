#ifndef CREACONFIG_H
#define CREACONFIG_H

#include <QDialog>
#include "Modele.h"
#include <QString>
#include "loadConfig.h"
#include "simulateur.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QGridLayout>

namespace Ui {
class CreaConfig;
}

class CreaConfig : public QDialog
{
    Q_OBJECT

public:
    explicit CreaConfig(QWidget *parent = nullptr, Simulateur * simu = nullptr);
    ~CreaConfig();

private slots:
    void on_btnTaille_clicked();

private:
    Ui::CreaConfig *ui;
    Reseau * res;
    Simulateur * simu;
    Configuration* config_cour;
    void chargerGrille();
    void clearLayout(QLayout* layout);
    void changeEtat(int i,int y,Configuration* config, QPushButton* button);
};

#endif // CREACONFIG_H
