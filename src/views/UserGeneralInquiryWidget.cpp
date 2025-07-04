#include "UserGeneralInquiryWidget.h"
#include "ui_usergeneralinquirywidget.h"

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
