#include "UserProductComplaintPage.h"
#include "ui_user_product_complaint_page.h"

UserProductComplaintPage::UserProductComplaintPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserProductComplaintPage)
{
    ui->setupUi(this);
}

UserProductComplaintPage::~UserProductComplaintPage()
{
    delete ui;
}
