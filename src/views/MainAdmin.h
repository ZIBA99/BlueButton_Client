#ifndef MAINADMIN_H
#define MAINADMIN_H

#include <QMainWindow>

namespace Ui {
class MainAdmin;
}

class MainAdmin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainAdmin(QWidget *parent = nullptr);
    ~MainAdmin();

private:
    Ui::MainAdmin *ui;
};

#endif // MAINADMIN_H
