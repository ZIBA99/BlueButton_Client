#ifndef EDUCATIONINFOAPPLICATIONWIDGET_H
#define EDUCATIONINFOAPPLICATIONWIDGET_H

#include <QWidget>

namespace Ui {
class EducationInfoApplicationWidget;
}

class EducationInfoApplicationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EducationInfoApplicationWidget(QWidget *parent = nullptr);
    ~EducationInfoApplicationWidget();

private:
    Ui::EducationInfoApplicationWidget *ui;
};

#endif // EDUCATIONINFOAPPLICATIONWIDGET_H
