#ifndef USEREDUCATIONMAINPAGE_H
#define USEREDUCATIONMAINPAGE_H

#include <QWidget>

namespace Ui {
class UserEducationMainPage;
}

class UserEducationMainPage : public QWidget
{
    Q_OBJECT

public:
    explicit UserEducationMainPage(QWidget *parent = nullptr);
    ~UserEducationMainPage();

private:
    Ui::UserEducationMainPage *ui;
};

#endif // USEREDUCATIONMAINPAGE_H
