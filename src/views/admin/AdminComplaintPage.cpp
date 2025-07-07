#include "AdminComplaintPage.h"
#include "ui_admin_complaint_page.h"

AdminComplaintPage::AdminComplaintPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminComplaintPage)
{
    ui->setupUi(this);
}

AdminComplaintPage::~AdminComplaintPage()
{
    delete ui;
}
