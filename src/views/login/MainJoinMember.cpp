#include "MainJoinMember.h"
#include "ui_join_member_main_window.h"


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
