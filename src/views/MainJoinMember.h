#ifndef MAINJOINMEMBER_H
#define MAINJOINMEMBER_H

#include <QMainWindow>
//#include "MainLogin.h"

QT_BEGIN_NAMESPACE

class MainLogin;

namespace Ui {
class MainJoinMember;  // MainJoinMember 변경
}
QT_END_NAMESPACE

class MainJoinMember : public QMainWindow  // MainWindow로 변경
{
    Q_OBJECT

public:
    MainJoinMember(QWidget *parent = nullptr);
    ~MainJoinMember();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainJoinMember *ui;
    MainLogin *mainLoginWindow;
};

#endif // MAINJOINMEMBER_H
