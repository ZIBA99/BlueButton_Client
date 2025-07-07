#include "UserSelfHelpWidget.h"
#include "ui_user_self_help_widget.h"

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
