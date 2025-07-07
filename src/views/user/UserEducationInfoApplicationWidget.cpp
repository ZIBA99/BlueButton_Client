#include "UserEducationInfoApplicationWidget.h"
#include "ui_user_education_info_application_widget.h"

UserEducationInfoApplicationWidget::UserEducationInfoApplicationWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserEducationInfoApplicationWidget)
{
    ui->setupUi(this);
}

UserEducationInfoApplicationWidget::~UserEducationInfoApplicationWidget()
{
    delete ui;
}
