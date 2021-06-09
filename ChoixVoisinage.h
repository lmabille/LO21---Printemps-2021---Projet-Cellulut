#ifndef CHOIXVOISINAGE_H
#define CHOIXVOISINAGE_H

#include "voisinage.h"

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

#include <QComboBox>
#include <QSpinBox>

class ChoixVonNeumann : public QWidget
{
    // Boutons
    Q_OBJECT
    QSpinBox* choixRayon;
public:
    explicit ChoixVonNeumann(QWidget* parent = nullptr); // à modifier
};

class ChoixVoisinage : public QWidget
{
    // Boutons
    Q_OBJECT
    QComboBox*listeVois;


    // Layouts

public:
    // Constructeur
    explicit ChoixVoisinage(QWidget* parent = nullptr); // à modifier ensuite

};

#endif // CHOIXVOISINAGE_H
