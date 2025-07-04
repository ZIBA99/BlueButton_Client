#include "UserEducationInfoApplicationWidget.h"
#include "ui_usereducationinfoapplicationwidget.h"

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
