#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class UserMainWindow;//mainuser.ui 이름이랑 일치
}
QT_END_NAMESPACE

class UserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    UserMainWindow(QWidget *parent = nullptr);
    ~UserMainWindow();

private:
    Ui::UserMainWindow *ui;
};
#endif // USERMAINWINDOW_H


