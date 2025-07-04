#ifndef ADMINCOMPLAINTSANDIMPROVEMENTSWIDGET_H
#define ADMINCOMPLAINTSANDIMPROVEMENTSWIDGET_H

#include <QWidget>

namespace Ui {
class AdminComplaintsAndImprovementsWidget;
}

class AdminComplaintsAndImprovementsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminComplaintsAndImprovementsWidget(QWidget *parent = nullptr);
    ~AdminComplaintsAndImprovementsWidget();

private:
    Ui::AdminComplaintsAndImprovementsWidget *ui;
};

#endif // ADMINCOMPLAINTSANDIMPROVEMENTSWIDGET_H
