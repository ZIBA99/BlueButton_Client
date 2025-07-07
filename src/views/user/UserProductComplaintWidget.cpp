#include "UserProductComplaintWidget.h"
#include "ui_user_product_complaint_widget.h"

UserProductComplaintWidget::UserProductComplaintWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserProductComplaintWidget)
{
    ui->setupUi(this);
}

UserProductComplaintWidget::~UserProductComplaintWidget()
{
    delete ui;
}
