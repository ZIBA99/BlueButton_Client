#include "UserMainWindow.h"
#include "ui_user_main_window.h"

UserMainWindow::UserMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);

}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}
