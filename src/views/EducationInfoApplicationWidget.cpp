#include "EducationInfoApplicationWidget.h"
#include "ui_educationinfoapplicationwidget.h"

EducationInfoApplicationWidget::EducationInfoApplicationWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EducationInfoApplicationWidget)
{
    ui->setupUi(this);
}

EducationInfoApplicationWidget::~EducationInfoApplicationWidget()
{
    delete ui;
}
