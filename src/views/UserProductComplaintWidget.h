#ifndef USERPRODUCTCOMPLAINTWIDGET_H
#define USERPRODUCTCOMPLAINTWIDGET_H

#include <QWidget>

namespace Ui {
class UserProductComplaintWidget;
}

class UserProductComplaintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserProductComplaintWidget(QWidget *parent = nullptr);
    ~UserProductComplaintWidget();

private:
    Ui::UserProductComplaintWidget *ui;
};

#endif // USERPRODUCTCOMPLAINTWIDGET_H
