#include "AdminDefaultPage.h"
#include "ui_admin_default_page.h"

AdminDefaultPage::AdminDefaultPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminDefaultPage)
{
    ui->setupUi(this);
}

AdminDefaultPage::~AdminDefaultPage()
{
    delete ui;
}
