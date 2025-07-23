#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>

namespace Ui {
class UserMainWindow;
}

class UserMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UserMainWindow(QWidget *parent = nullptr);
    ~UserMainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragLeaveEvent(QDragLeaveEvent* event) override;
    void dropEvent(QDropEvent* event) override;



private:
    Ui::UserMainWindow *ui;
    QWidget* findWidgetByName(const QString& name)
    {
        // 전역에서 위젯 찾기 로직
        return QApplication::activeWindow()->findChild<QWidget*>(name);
    }
};

#endif // USERMAINWINDOW_H
