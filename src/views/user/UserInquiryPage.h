#ifndef USERINQUIRYPAGE_H
#define USERINQUIRYPAGE_H

#include <QWidget>

namespace Ui {
class UserInquiryPage;
}

class UserInquiryPage : public QWidget
{
    Q_OBJECT

public:
    explicit UserInquiryPage(QWidget *parent = nullptr);
    ~UserInquiryPage();

private:
    Ui::UserInquiryPage *ui;
};

#endif // USERINQUIRYPAGE_H
