#include "MainLogin.h"
#include "ui_main_login.h"


MainLogin::MainLogin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLogin) , mainJoinMemberWindow(nullptr)
{
    ui->setupUi(this);

}

MainLogin::~MainLogin()
{
    delete ui;
}

void MainLogin::on_pushButton_2_clicked()
{
    if (!mainJoinMemberWindow) {  // 변수명 수정
        mainJoinMemberWindow = new MainJoinMember(this);
    }
    mainJoinMemberWindow->show();
    this->hide();         // 현재 로그인 창을 화면에서 숨김 (선택적 동작)
}

