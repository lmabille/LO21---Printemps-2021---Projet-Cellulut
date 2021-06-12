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

class choixEtats : public QWidget
{

    std::string transition;

    Voisinage *voi;

    //Les indices des états
    QTableWidget *indicesE;

    //Les labels
    QTableWidget *labelsE;

    //Les couleurs voir comment Thomas a fait
    QTableWidget *couleursE;


    //Boutons fenêtres
    Q_OBJECT

    QPushButton *valider;
    QLabel *titre;

    //Les layout

    QVBoxLayout *ensemble;




public:
    // Constructeur
    explicit choixEtats(QWidget* parent = nullptr, Voisinage *v=nullptr, std::string tr="" );

private slots:
 //   void afficher_taille_reseaux();



   void Validation();

};




#endif // CHOIXETATS_H
