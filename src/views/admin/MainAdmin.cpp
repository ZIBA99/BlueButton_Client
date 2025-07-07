#include "MainAdmin.h"
#include "ui_admin_main_window.h"

MainAdmin::MainAdmin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainAdmin)
{
    ui->setupUi(this);
}

MainAdmin::~MainAdmin()
{
    delete ui;
}
