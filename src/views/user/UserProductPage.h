#ifndef USERPRODUCTPAGE_H
#define USERPRODUCTPAGE_H

#include <QWidget>

namespace Ui {
class UserProductPage;
}

class UserProductPage : public QWidget
{
    Q_OBJECT

public:
    explicit UserProductPage(QWidget *parent = nullptr);
    ~UserProductPage();

private:
    Ui::UserProductPage *ui;
};

#endif // USERPRODUCTPAGE_H
