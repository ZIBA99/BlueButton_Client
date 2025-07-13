#include "UserMainWindow.h"
#include "ui_user_main_window.h"

UserMainWindow::UserMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    defaultPage = new UserDefaultPage;
    usereducationchatpage = new UserEducationChatPage;
    usereducationpage = new UserEducationMainPage;
    userinquirypage = new UserInquiryPage;
    userproductpage = new UserProductPage;
    userproductcomplainpage = new UserProductComplaintPage;
    userselfhelpage = new UserSelfHelpPage;

    ui->mainLayout->insertWidget(0,defaultPage);

}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

void UserMainWindow::setEmptyPageLayout(){
    defaultPage->setParent(NULL);
    usereducationchatpage->setParent(NULL);
    usereducationpage->setParent(NULL);
    defaultPage->setParent(NULL);
    userinquirypage->setParent(NULL);
    userproductpage->setParent(NULL);
    userproductcomplainpage->setParent(NULL);
    userselfhelpage->setParent(NULL);
}

void UserMainWindow::on_product_page_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(userproductpage);
}


void UserMainWindow::on_education_main_page_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(usereducationpage);
}


void UserMainWindow::on_education_chat_page_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(usereducationchatpage);
}


void UserMainWindow::on_self_help_page_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(userselfhelpage);
}


void UserMainWindow::on_praduct_complain_page_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(userproductcomplainpage);
}


void UserMainWindow::on_genernal_inquory_page_clicked()
{
    setEmptyPageLayout();
    ui->mainLayout->addWidget(userinquirypage);
}

