#ifndef SIMU_H
#define SIMU_H

#include <QMainWindow>

namespace Ui {
class simu;
}

class simu : public QMainWindow
{
    Q_OBJECT

public:
    explicit simu(QWidget *parent = nullptr);
    ~simu();

private:
    Ui::simu *ui;
};

#endif // SIMU_H
