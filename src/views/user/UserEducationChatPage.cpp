#include "UserEducationChatPage.h"
#include "ui_user_education_chat_page.h"

UserEducationChatPage::UserEducationChatPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserEducationChatPage)
{
    ui->setupUi(this);
}

UserEducationChatPage::~UserEducationChatPage()
{
    delete ui;
}
