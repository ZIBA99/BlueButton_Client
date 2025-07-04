#include "UserSelfHelpWidget.h"
#include "ui_userselfhelpwidget.h"

UserSelfHelpWidget::UserSelfHelpWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserSelfHelpWidget)
{
    ui->setupUi(this);
}

UserSelfHelpWidget::~UserSelfHelpWidget()
{
    delete ui;
}
