#include "MainLogin.h"
#include "ui_main_login.h"


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
