#include "UserMainWindow.h"
#include "ui_user_main_window.h"

UserMainWindow::UserMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    defaultPage = new UserDefaultPage;
    userEducationChatPage = new UserEducationChatPage;
    userEducationPage = new UserEducationMainPage;
    userInquiryPage = new UserInquiryPage;
    userProductPage = new UserProductPage;
    userProductComplainPage = new UserProductComplaintPage;
    userSelfHelpPage = new UserSelfHelpPage;

    ui->mainLayout->insertWidget(0,defaultPage);

}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

void UserMainWindow::setEmptyPageLayout(){
    defaultPage->setParent(NULL);
    userEducationChatPage->setParent(NULL);
    userEducationPage->setParent(NULL);
    userInquiryPage->setParent(NULL);
    userProductPage->setParent(NULL);
    userProductComplainPage->setParent(NULL);
    userSelfHelpPage->setParent(NULL);
}

void UserMainWindow::on_product_page_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(userProductPage);
}


void UserMainWindow::on_education_main_page_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(userEducationPage);
}


void UserMainWindow::on_education_chat_page_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(userEducationChatPage);
}


void UserMainWindow::on_self_help_page_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(userSelfHelpPage);
}


void UserMainWindow::on_praduct_complain_page_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(userProductComplainPage);
}


void UserMainWindow::on_genernal_inquory_page_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(userInquiryPage);
}

