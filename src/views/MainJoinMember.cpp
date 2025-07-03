#include "MainJoinMember.h"
#include "ui_main_joinmember.h"


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
