#ifndef USEREDUCATIONINFOAPPLICATIONWIDGET_H
#define USEREDUCATIONINFOAPPLICATIONWIDGET_H

#include <QWidget>

namespace Ui {
class UserEducationInfoApplicationWidget;
}

class UserEducationInfoApplicationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserEducationInfoApplicationWidget(QWidget *parent = nullptr);
    ~UserEducationInfoApplicationWidget();

private:
    Ui::UserEducationInfoApplicationWidget *ui;
};

#endif // USEREDUCATIONINFOAPPLICATIONWIDGET_H
