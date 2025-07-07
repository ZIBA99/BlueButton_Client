#include "MainJoinMember.h"
#include "ui_main_joinmember.h"
#include "mainlogin.h"

MainJoinMember::MainJoinMember(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainJoinMember)
{
    ui->setupUi(this);

}

MainJoinMember::~MainJoinMember()
{
    delete ui;
}

void MainJoinMember::on_pushButton_clicked()
{
    if(!mainLoginWindow){
        mainLoginWindow = new MainLogin(this);
    }
    mainLoginWindow -> show();
    this -> hide();
 }

