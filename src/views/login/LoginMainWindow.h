#ifndef LOGINMAINWINDOW_H
#define LOGINMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
class LoginMainWindow;  // MainWindow로 변경
}
QT_END_NAMESPACE

class LoginMainWindow : public QMainWindow  // MainWindow로 변경
{
    Q_OBJECT

public:
    LoginMainWindow(QWidget *parent = nullptr);
    ~LoginMainWindow();

private:
    Ui::LoginMainWindow *ui;  // MainLogin 변경
};
#endif // LOGINMAINWINDOW_H
