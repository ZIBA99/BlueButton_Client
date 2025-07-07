#include "CentralManagement.h"
#include "ui_central_management.h"

CentralManagement::CentralManagement(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CentralManagement)
{
    ui->setupUi(this);
}

CentralManagement::~CentralManagement()
{
    delete ui;
}
