#ifndef USERSELFHELPPAGE_H
#define USERSELFHELPPAGE_H

#include <QWidget>

namespace Ui {
class UserSelfHelpPage;
}

class UserSelfHelpPage : public QWidget
{
    Q_OBJECT

public:
    explicit UserSelfHelpPage(QWidget *parent = nullptr);
    ~UserSelfHelpPage();

private:
    Ui::UserSelfHelpPage *ui;
};

#endif // USERSELFHELPPAGE_H
