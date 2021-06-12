#ifndef INFORMATIONS_H
#define INFORMATIONS_H

#include <QDialog>
#include "Modele.h"

namespace Ui {
class informations;
}

class informations : public QDialog
{
    Q_OBJECT

public:
    explicit informations(QWidget *parent = nullptr);
    ~informations();

private:
    Ui::informations *ui;
    Modele * M;
};

#endif // INFORMATIONS_H
