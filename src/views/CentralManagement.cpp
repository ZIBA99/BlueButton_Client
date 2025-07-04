#include "CentralManagement.h"
#include "ui_centralmanagement.h"

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
