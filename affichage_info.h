#ifndef AFFICHAGE_INFO_H
#define AFFICHAGE_INFO_H
#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QString>
#include <QVBoxLayout>

class information : public QWidget{
Q_OBJECT;
QSpinBox* num; // numéro
QLineEdit* numeroBit[8]; // un QLineEdit par bit
QLabel* numl;
QLabel* numeroBitl[8];
QVBoxLayout* numc;
QVBoxLayout* bitc[8];
QHBoxLayout* numeroc;
QIntValidator* zeroOneValidator;
public:
explicit information(QWidget* parent = nullptr);
private slots:

};
#endif // AFFICHAGE_INFO_H
