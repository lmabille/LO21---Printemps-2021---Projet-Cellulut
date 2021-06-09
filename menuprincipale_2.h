#ifndef MENUPRINCIPALE_2_H
#define MENUPRINCIPALE_2_H

#include <QDialog>

namespace Ui {
class MenuPrincipale_2;
}

class MenuPrincipale_2 : public QDialog
{
    Q_OBJECT

public:
    explicit MenuPrincipale_2(QWidget *parent = nullptr);
    ~MenuPrincipale_2();

private:
    Ui::MenuPrincipale_2 *ui;
};

#endif // MENUPRINCIPALE_2_H
