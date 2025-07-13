#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>
#include "UserDefaultPage.h"
#include "UserProductPage.h"
#include "UserEducationMainPage.h"
#include "UserEducationChatPage.h"
#include "UserSelfHelpPage.h"
#include "UserProductComplaintPage.h"
#include "UserInquiryPage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class UserMainWindow;//mainuser.ui 이름이랑 일치
}
QT_END_NAMESPACE

class UserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserMainWindow(QWidget *parent = nullptr);
    ~UserMainWindow();

private slots:
    void on_product_page_clicked();

    void on_education_main_page_clicked();

    void on_education_chat_page_clicked();

    void on_self_help_page_clicked();

    void on_praduct_complain_page_clicked();

    void on_genernal_inquory_page_clicked();

private:
    Ui::UserMainWindow *ui;
    UserDefaultPage *defaultPage;
    UserEducationChatPage *usereducationchatpage;
    UserEducationMainPage *usereducationpage;
    UserInquiryPage *userinquirypage;
    UserProductPage *userproductpage;
    UserProductComplaintPage *userproductcomplainpage;
    UserSelfHelpPage *userselfhelpage;

    void setEmptyPageLayout();
};
#endif // USERMAINWINDOW_H


