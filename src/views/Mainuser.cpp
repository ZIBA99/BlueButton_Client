#include "Mainuser.h"
#include "ui_main_user.h"

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
