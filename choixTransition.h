#ifndef CHOIXTRANSITION_H
#define CHOIXTRANSITION_H

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

class choixTransition : public QWidget
{

    std::string transition;

    //Boutons fenêtres
    Q_OBJECT
    QListWidget *choix;
    QPushButton *valider;
    QLabel *titre;

    //Les layout

    QVBoxLayout *ensemble;




public:
    // Constructeur
    explicit choixTransition(QWidget* parent = nullptr);

private slots:
 //   void afficher_taille_reseaux();

   void SelectionTr();

   void Validation();

};






#endif // CHOIXTRANSITION_H
