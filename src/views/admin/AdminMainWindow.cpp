#include "AdminMainWindow.h"
#include "ui_admin_main_window.h"

AdminMainWindow::AdminMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);
    defaultPage = new AdminDefaultPage;
    complaintPage = new AdminComplaintPage;
    inquiryPage = new AdminInquiryPage;
    ui->mainLayout->insertWidget(0,defaultPage);
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}

void AdminMainWindow::setEmptyPageLayout(){
    defaultPage->setParent(NULL);
    complaintPage->setParent(NULL);
    inquiryPage->setParent(NULL);
}

void AdminMainWindow::on_pushButton_complaint_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(complaintPage);
}

void AdminMainWindow::on_pushButton_inquiry_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(inquiryPage);
}

