#ifndef USERPRODUCTCOMPLAINTPAGE_H
#define USERPRODUCTCOMPLAINTPAGE_H

#include <QWidget>

namespace Ui {
class UserProductComplaintPage;
}

class UserProductComplaintPage : public QWidget
{
    Q_OBJECT

public:
    explicit UserProductComplaintPage(QWidget *parent = nullptr);
    ~UserProductComplaintPage();

private:
    Ui::UserProductComplaintPage *ui;
};

#endif // USERPRODUCTCOMPLAINTPAGE_H
