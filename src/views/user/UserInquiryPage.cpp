#include "UserInquiryPage.h"
#include "ui_user_general_inquiry_page.h"

UserInquiryPage::UserInquiryPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserInquiryPage)
{
    ui->setupUi(this);
}

UserInquiryPage::~UserInquiryPage()
{
    delete ui;
}
