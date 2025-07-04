#include "UserProductComplaintWidget.h"
#include "ui_userproductcomplaintwidget.h"

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
