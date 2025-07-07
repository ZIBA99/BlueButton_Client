#include "UserEducationCommunicationWidget.h"
#include "ui_user_education_communication_widget.h"

UserEducationCommunicationWidget::UserEducationCommunicationWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserEducationCommunicationWidget)
{
    ui->setupUi(this);
}

UserEducationCommunicationWidget::~UserEducationCommunicationWidget()
{
    delete ui;
}
