#include "UserProductWidget.h"
#include "ui_user_product_widget.h"

UserProductWidget::UserProductWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserProductWidget)
{
    ui->setupUi(this);
}

UserProductWidget::~UserProductWidget()
{
    delete ui;
}
