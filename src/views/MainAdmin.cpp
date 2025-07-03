#include "MainAdmin.h"
#include "ui_main_admin.h"

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
