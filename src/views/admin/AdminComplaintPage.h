#ifndef ADMINCOMPLAINTPAGE_H
#define ADMINCOMPLAINTPAGE_H

#include <QWidget>

namespace Ui {
class AdminComplaintPage;
}

class AdminComplaintPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminComplaintPage(QWidget *parent = nullptr);
    ~AdminComplaintPage();

private:
    Ui::AdminComplaintPage *ui;
};

#endif // ADMINCOMPLAINTPAGE_H
