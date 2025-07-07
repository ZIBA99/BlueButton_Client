#include "UserProductPage.h"
#include "ui_user_product_page.h"

UserProductPage::UserProductPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserProductPage)
{
    ui->setupUi(this);
}

UserProductPage::~UserProductPage()
{
    delete ui;
}
