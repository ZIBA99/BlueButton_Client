#ifndef USEREDUCATIONCOMMUNICATIONWIDGET_H
#define USEREDUCATIONCOMMUNICATIONWIDGET_H

#include <QWidget>

namespace Ui {
class UserEducationCommunicationWidget;
}

class UserEducationCommunicationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserEducationCommunicationWidget(QWidget *parent = nullptr);
    ~UserEducationCommunicationWidget();

private:
    Ui::UserEducationCommunicationWidget *ui;
};

#endif // USEREDUCATIONCOMMUNICATIONWIDGET_H
