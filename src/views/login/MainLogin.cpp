#include "MainLogin.h"
#include "ui_login_main_window.h"


MainLogin::MainLogin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLogin)
{
    ui->setupUi(this);

}

MainLogin::~MainLogin()
{
    delete ui;
}
