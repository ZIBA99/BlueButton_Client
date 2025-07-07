#include "Mainuser.h"
#include "ui_user_main_window.h"

MainUser::MainUser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainUser)
{
    ui->setupUi(this);

}

MainUser::~MainUser()
{
    delete ui;
}
