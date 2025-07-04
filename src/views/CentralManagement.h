#ifndef CENTRALMANAGEMENT_H
#define CENTRALMANAGEMENT_H

#include <QWidget>

namespace Ui {
class CentralManagement;
}

class CentralManagement : public QWidget
{
    Q_OBJECT

public:
    explicit CentralManagement(QWidget *parent = nullptr);
    ~CentralManagement();

private:
    Ui::CentralManagement *ui;
};

#endif // CENTRALMANAGEMENT_H
