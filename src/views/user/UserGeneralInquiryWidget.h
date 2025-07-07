#ifndef USERGENERALINQUIRYWIDGET_H
#define USERGENERALINQUIRYWIDGET_H

#include <QWidget>

namespace Ui {
class UserGeneralInquiryWidget;
}

class UserGeneralInquiryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserGeneralInquiryWidget(QWidget *parent = nullptr);
    ~UserGeneralInquiryWidget();

private:
    Ui::UserGeneralInquiryWidget *ui;
};

#endif // USERGENERALINQUIRYWIDGET_H
