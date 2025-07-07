#ifndef USEREDUCATIONCHATPAGE_H
#define USEREDUCATIONCHATPAGE_H

#include <QWidget>

namespace Ui {
class UserEducationChatPage;
}

class UserEducationChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit UserEducationChatPage(QWidget *parent = nullptr);
    ~UserEducationChatPage();

private:
    Ui::UserEducationChatPage *ui;
};

#endif // USEREDUCATIONCHATPAGE_H
