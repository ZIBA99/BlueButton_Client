#ifndef MAINLOGIN_H
#define MAINLOGIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainLogin;  // MainWindow로 변경
}
QT_END_NAMESPACE

class MainLogin : public QMainWindow  // MainWindow로 변경
{
    Q_OBJECT

public:
    MainLogin(QWidget *parent = nullptr);
    ~MainLogin();

private:
    Ui::MainLogin *ui;  // MainLogin 변경
};
#endif // MAINLOGIN_H
