#include "UserGeneralInquiryWidget.h"
#include "ui_user_general_inquiry_widget.h"

UserGeneralInquiryWidget::UserGeneralInquiryWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserGeneralInquiryWidget)
{
    ui->setupUi(this);
}

UserGeneralInquiryWidget::~UserGeneralInquiryWidget()
{
    delete ui;
}
