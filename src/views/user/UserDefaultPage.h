#ifndef USERDEFAULTPAGE_H
#define USERDEFAULTPAGE_H

#include <QWidget>

namespace Ui {
class UserDefaultPage;
}

class UserDefaultPage : public QWidget
{
    Q_OBJECT

public:
    explicit UserDefaultPage(QWidget *parent = nullptr);
    ~UserDefaultPage();

private:
    Ui::UserDefaultPage *ui;
};

#endif // USERDEFAULTPAGE_H
