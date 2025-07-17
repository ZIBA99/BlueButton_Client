#include "AminEuducationChatPage.h"
#include "ui_amin_euducation_chat_page.h"

AminEuducationChatPage::AminEuducationChatPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AminEuducationChatPage)
{
    ui->setupUi(this);
}

AminEuducationChatPage::~AminEuducationChatPage()
{
    delete ui;
}
