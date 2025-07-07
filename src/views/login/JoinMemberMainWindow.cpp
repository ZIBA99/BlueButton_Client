#include "JoinMemberMainWindow.h"
#include "ui_join_member_main_window.h"


JoinMemberMainWindow::JoinMemberMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::JoinMemberMainWindow)
{
    ui->setupUi(this);

}

JoinMemberMainWindow::~JoinMemberMainWindow()
{
    delete ui;
}
