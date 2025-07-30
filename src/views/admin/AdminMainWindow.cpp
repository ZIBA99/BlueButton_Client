#include "AdminMainWindow.h"
#include "ui_admin_main_window.h"

AdminMainWindow::AdminMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}
