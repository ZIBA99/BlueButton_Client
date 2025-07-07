#ifndef ADMINDEFAULTPAGE_H
#define ADMINDEFAULTPAGE_H

#include <QWidget>

namespace Ui {
class AdminDefaultPage;
}

class AdminDefaultPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminDefaultPage(QWidget *parent = nullptr);
    ~AdminDefaultPage();

private:
    Ui::AdminDefaultPage *ui;
};

#endif // ADMINDEFAULTPAGE_H
