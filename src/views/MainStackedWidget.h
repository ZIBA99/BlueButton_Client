#ifndef MAINSTACKEDWIDGET_H
#define MAINSTACKEDWIDGET_H

#include <QWidget>

namespace Ui {
class MainStackedWidget;
}

class MainStackedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainStackedWidget(QWidget *parent = nullptr);
    ~MainStackedWidget();

private:
    Ui::MainStackedWidget *ui;
};

#endif // MAINSTACKEDWIDGET_H
