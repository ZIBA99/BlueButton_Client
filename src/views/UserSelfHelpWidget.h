#ifndef USERSELFHELPWIDGET_H
#define USERSELFHELPWIDGET_H

#include <QWidget>

namespace Ui {
class UserSelfHelpWidget;
}

class UserSelfHelpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserSelfHelpWidget(QWidget *parent = nullptr);
    ~UserSelfHelpWidget();

private:
    Ui::UserSelfHelpWidget *ui;
};

#endif // USERSELFHELPWIDGET_H
