#include "UserEducationMainPage.h"
#include "ui_user_education_main_page.h"

UserEducationMainPage::UserEducationMainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserEducationMainPage)
{
    ui->setupUi(this);
}

UserEducationMainPage::~UserEducationMainPage()
{
    delete ui;
}
