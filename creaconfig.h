#ifndef CREACONFIG_H
#define CREACONFIG_H

#include <QDialog>

namespace Ui {
class CreaConfig;
}

class CreaConfig : public QDialog
{
    Q_OBJECT

public:
    explicit CreaConfig(QWidget *parent = nullptr);
    ~CreaConfig();

private:
    Ui::CreaConfig *ui;
};

#endif // CREACONFIG_H
