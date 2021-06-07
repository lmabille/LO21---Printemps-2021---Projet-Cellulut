#ifndef TAILLE_RESEAU_H
#define TAILLE_RESEAU_H

#include <QDialog>

namespace Ui {
class taille_reseau;
}

class taille_reseau : public QDialog
{
    Q_OBJECT

public:
    explicit taille_reseau(QWidget *parent = nullptr);
    ~taille_reseau();

private:
    Ui::taille_reseau *ui;
};

#endif // TAILLE_RESEAU_H
