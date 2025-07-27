#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QGridLayout>
#include <QJsonArray>
#include <QMap>

#include "ProductWidget.h"
#include "src/controllers/ClientSocket.h"
#include "src/controllers/ImageDownloader.h"  // 추가
#include <QStandardItemModel>
#include "LoginMainWindow.h"
#include "ui_login_main_window.h"

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
    void onChatRoomListReceived(const QJsonArray &rooms);

    // ImageDownloader 관련 슬롯들
    void onImageDownloadCompleted(int requestId, const QString &fileName, const QString &savedPath);
    void onImageDownloadFailed(int requestId, const QString &fileName, const QString &error);
    void onImageDownloadProgress(int requestId, qint64 bytesReceived, qint64 totalBytes);

    void onChatRoomClicked(const QModelIndex& index);
    void openChatRoom(const QString& roomName);

    void onChatRoomJoined(const QJsonObject &chatRoom);
    void onChatRoomLeft(bool success);
    void onChatMessageSent(const QJsonObject &message);
    void onChatHistoryReceived(const QJsonArray &messages);
    void onChatMessageReceived(const QJsonObject &message);
    void requestChatRoomJoin(id_t roomId);

    void on_lineEdit_editingFinished();
    void onErrorOccurred(const QString &error);

private:
    Ui::UserMainWindow *ui;
    LoginMainWindow *m_login;
    QVector<ProductWidget*> productWidgets;
    ClientSocket *m_client;
    ImageDownloader *m_imageDownloader;  // 추가
    QStandardItemModel* model;
    id_t m_currentChatRoomId;

    // 다운로드 요청 추적용
    QMap<int, ProductWidget*> m_downloadRequests;  // requestId -> ProductWidget
    QMap<QString, ProductWidget*> m_fileNameToWidget; // fileName -> ProductWidget

    QGridLayout* getTargetLayoutAtPosition(const QPoint& pos);
    void rearrangeGridLayout(QGridLayout* layout, int maxColumns = 3);
    void switchMainView(UserMainView view);
    void connectServer();
    void connectImageDownloader();  // 추가
    void downloadProductImages();   // 추가
    void updateProductImage(ProductWidget* widget, const QString &imagePath);  // 추가
    void selectChatRoomById(id_t roomIdToSelect);

    void setProductImage(const QString &imagePath);
    bool loadImageWithReader(const QString &imagePath, QPixmap &pixmap);
    void setPixmapToButton(const QPixmap &pixmap, const QString &imagePath);

    QWidget* findWidgetByName(const QString& name)
    {
        // 전역에서 위젯 찾기 로직
        return QApplication::activeWindow()->findChild<QWidget*>(name);
    }
};

#endif // USERMAINWINDOW_H
