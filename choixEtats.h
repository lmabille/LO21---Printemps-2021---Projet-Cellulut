#ifndef CHOIXETATS_H
#define CHOIXETATS_H


#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QString>
#include <qboxlayout.h>
#include <QTableWidget>
#include <QHeaderView>
#include <QModelIndex>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include "voisinage.h"
#include "etat.h"

class ChoixEtats : public QWidget
{

    std::string transition;

    Voisinage *voi;


    //l'ensemble d'état
    EnsembleEtats *ee=nullptr;


    QHBoxLayout *ligneE[8];

    QLabel *indiceE[8];

    QLineEdit *labelE[8];



    //Boutons fenêtres
    Q_OBJECT

    QPushButton *valider;
    QLabel *titre;

    //Les layout

    QVBoxLayout *ensemble;




public:
    // Constructeur
    explicit ChoixEtats(QWidget* parent = nullptr, Voisinage *v=nullptr, std::string tr="" );

private slots:




void Validation();

};



#endif // CHOIXETATS_H
