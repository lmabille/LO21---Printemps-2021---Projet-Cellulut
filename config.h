#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>

namespace Ui {
class config;
}

class config : public QDialog
{
    Q_OBJECT

public:
    explicit config(QWidget *parent = nullptr);
    ~config();

private:
    Ui::config *ui;
};

#endif // CONFIG_H
