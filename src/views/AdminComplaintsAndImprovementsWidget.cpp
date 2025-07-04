#include "AdminComplaintsAndImprovementsWidget.h"
#include "ui_admincomplaintsandimprovementswidget.h"

AdminComplaintsAndImprovementsWidget::AdminComplaintsAndImprovementsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminComplaintsAndImprovementsWidget)
{
    ui->setupUi(this);
}

AdminComplaintsAndImprovementsWidget::~AdminComplaintsAndImprovementsWidget()
{
    delete ui;
}
