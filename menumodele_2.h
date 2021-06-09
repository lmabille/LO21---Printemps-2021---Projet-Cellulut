#ifndef MENUMODELE_2_H
#define MENUMODELE_2_H

#include <QWidget>

namespace Ui {
class MenuModele_2;
}

class MenuModele_2 : public QWidget
{
    Q_OBJECT

public:
    explicit MenuModele_2(QWidget *parent = nullptr);
    ~MenuModele_2();

private:
    Ui::MenuModele_2 *ui;
};

#endif // MENUMODELE_2_H
