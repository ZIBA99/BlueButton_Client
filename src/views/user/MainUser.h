#ifndef MAINUSER_H
#define MAINUSER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainUser;//mainuser.ui 이름이랑 일치
}
QT_END_NAMESPACE

class MainUser : public QMainWindow
{
    Q_OBJECT

public:
    MainUser(QWidget *parent = nullptr);
    ~MainUser();

private:
    Ui::MainUser *ui;
};
#endif // MAINUSER_H


