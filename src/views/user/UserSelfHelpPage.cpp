#include "UserSelfHelpPage.h"
#include "ui_user_self_help_page.h"

UserSelfHelpPage::UserSelfHelpPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserSelfHelpPage)
{
    ui->setupUi(this);
}

UserSelfHelpPage::~UserSelfHelpPage()
{
    delete ui;
}
