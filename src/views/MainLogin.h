#ifndef MAINLOGIN_H
#define MAINLOGIN_H

#include <QMainWindow>
#include "MainJoinMember.h"  // 회원가입 창 클래스 헤더 파일명에 맞게 수정

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

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MainLogin *ui;  // MainLogin 변경
    MainJoinMember *mainJoinMemberWindow;  // 회원가입 창 객체 포인터
};
#endif // MAINLOGIN_H
