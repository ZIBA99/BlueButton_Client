#ifndef USERPRODUCTWIDGET_H
#define USERPRODUCTWIDGET_H

#include <QWidget>

namespace Ui {
class UserProductWidget;
}

class UserProductWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserProductWidget(QWidget *parent = nullptr);
    ~UserProductWidget();

private:
    Ui::UserProductWidget *ui;
};

#endif // USERPRODUCTWIDGET_H
