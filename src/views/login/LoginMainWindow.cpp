#include "LoginMainWindow.h"
#include "ui_login_main_window.h"


LoginMainWindow::LoginMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginMainWindow)
{
    ui->setupUi(this);

}

LoginMainWindow::~LoginMainWindow()
{
    delete ui;
}
