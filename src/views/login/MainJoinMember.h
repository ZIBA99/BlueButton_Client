#ifndef MAINJOINMEMBER_H
#define MAINJOINMEMBER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainJoinMember;  // MainJoinMember 변경
}
QT_END_NAMESPACE

class MainJoinMember : public QMainWindow  // MainWindow로 변경
{
    Q_OBJECT

public:
    MainJoinMember(QWidget *parent = nullptr);
    ~MainJoinMember();

private:
    Ui::MainJoinMember *ui;
};

#endif // MAINJOINMEMBER_H
