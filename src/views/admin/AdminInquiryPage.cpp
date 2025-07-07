#include "AdminInquiryPage.h"
#include "ui_admin_inquiry_page.h"

AdminInquiryPage::AdminInquiryPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminInquiryPage)
{
    ui->setupUi(this);
}

AdminInquiryPage::~AdminInquiryPage()
{
    delete ui;
}
