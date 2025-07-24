#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QGridLayout>
#include <QJsonArray>

#include "ProductWidget.h"
#include "src/controllers/ClientSocket.h"

enum class UserMainView {
    Shop = 0,
    Chat = 1,
    Data = 2
};
#define PRODUCT_LIST_COL_SIZE 4

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




private slots:
    void on_pushButton_shop_clicked();
    void on_pushButton_chat_clicked();
    void onAnyProductDoubleClicked();
    void onProductListReceived(const QJsonArray &products);


private:
    Ui::UserMainWindow *ui;
    QVector<ProductWidget*> productWidgets;
    ClientSocket *m_client;


    QGridLayout* getTargetLayoutAtPosition(const QPoint& pos);
    void rearrangeGridLayout(QGridLayout* layout, int maxColumns = 3);
    void switchMainView(UserMainView view);
    void connectServer();
    QWidget* findWidgetByName(const QString& name)
    {
        // 전역에서 위젯 찾기 로직
        return QApplication::activeWindow()->findChild<QWidget*>(name);
    }


};

#endif // USERMAINWINDOW_H
