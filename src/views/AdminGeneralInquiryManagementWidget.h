#ifndef ADMINGENERALINQUIRYMANAGEMENTWIDGET_H
#define ADMINGENERALINQUIRYMANAGEMENTWIDGET_H

#include <QWidget>

namespace Ui {
class AdminGeneralInquiryManagementWidget;
}

class AdminGeneralInquiryManagementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminGeneralInquiryManagementWidget(QWidget *parent = nullptr);
    ~AdminGeneralInquiryManagementWidget();

private:
    Ui::AdminGeneralInquiryManagementWidget *ui;
};

#endif // ADMINGENERALINQUIRYMANAGEMENTWIDGET_H
