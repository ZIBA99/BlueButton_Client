#include "UserDefaultPage.h"
#include "ui_user_default_page.h"

UserDefaultPage::UserDefaultPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserDefaultPage)
{
    ui->setupUi(this);
}

UserDefaultPage::~UserDefaultPage()
{
    delete ui;
}
