#ifndef JOINMEMBERMAINWINDOW_H
#define JOINMEMBERMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class JoinMemberMainWindow;  // MainJoinMember 변경
}
QT_END_NAMESPACE

class JoinMemberMainWindow : public QMainWindow  // MainWindow로 변경
{
    Q_OBJECT

public:
    JoinMemberMainWindow(QWidget *parent = nullptr);
    ~JoinMemberMainWindow();

private:
    Ui::JoinMemberMainWindow *ui;
};

#endif // JOINMEMBERMAINWINDOW_H
