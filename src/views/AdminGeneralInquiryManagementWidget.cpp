#include "AdminGeneralInquiryManagementWidget.h"
#include "ui_admingeneralinquirymanagementwidget.h"

AdminGeneralInquiryManagementWidget::AdminGeneralInquiryManagementWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminGeneralInquiryManagementWidget)
{
    ui->setupUi(this);
}

AdminGeneralInquiryManagementWidget::~AdminGeneralInquiryManagementWidget()
{
    delete ui;
}
