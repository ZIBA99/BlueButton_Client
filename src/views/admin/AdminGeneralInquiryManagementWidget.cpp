#include "AdminGeneralInquiryManagementWidget.h"
#include "ui_admin_general_inquiry_management_widget.h"

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
