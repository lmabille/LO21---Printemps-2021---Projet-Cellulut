#ifndef MENU_CONFIG_H
#define MENU_CONFIG_H

#include <QDialog>

namespace Ui {
class menu_config;
}

class menu_config : public QDialog
{
    Q_OBJECT

public:
    explicit menu_config(QWidget *parent = nullptr);
    ~menu_config();

private:
    Ui::menu_config *ui;
};

#endif // MENU_CONFIG_H
