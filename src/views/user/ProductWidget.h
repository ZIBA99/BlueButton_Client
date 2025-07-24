#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include "src/models/entity/Entity.h"
#include "src/models/entity/Product.h"
#include "DoubleClickButton.h"

namespace Ui {
class ProductWidget;
}

class ProductWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductWidget(QWidget *parent = nullptr);
    ~ProductWidget();

    // 기존 메서드들
    id_t getChatRoomId();
    void setChatRoomId(id_t roomId);
    void setInfo(id_t id, id_t roomId, QString category, QString name, qreal price, qint32 stock);
    void setInfo(id_t id, id_t roomId, QString category, QString name, qreal price, qint32 stock, const QString &imageFileName);

    // 이미지 관련 새로운 메서드들
    void setProductImage(const QString &imagePath);
    void setDefaultImage();
    QString getImageFileName() const { return m_imageFileName; }
    void setImageFileName(const QString &fileName) { m_imageFileName = fileName; }

    QLabel *productNameLabel;
    DoubleClickButton *productImageButton;
    Product info;

signals:
    void doubleClicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    Ui::ProductWidget *ui;
    QPoint m_dragStartPosition;

    // product info
    id_t m_id = -1;
    id_t m_roomId = -1;
    QString m_category;
    QString m_name;
    qreal m_price;
    qint32 m_stock;
    QString m_imageFileName;  // 추가: 이미지 파일명

    int clicked_cnt = 0;

    // 이미지 관련 private 메서드들
    QPixmap scaleImageToButton(const QPixmap &originalPixmap) const;
    QString getDefaultImagePath() const;

    // 강력한 이미지 로딩 메서드들
    bool loadImageWithReader(const QString &imagePath, QPixmap &pixmap);
    bool loadImageFromBytes(const QString &imagePath, QPixmap &pixmap);
    bool repairAndLoadPng(const QString &imagePath, const QString &repairedPath, QPixmap &pixmap);

    // PNG 복구 관련 메서드들
    QByteArray repairPngChunks(const QByteArray &originalData);
    void debugImageFile(const QString &imagePath);
    void analyzePngChunks(const QByteArray &data);
    void setPixmapToButton(const QPixmap &pixmap, const QString &imagePath);
};

#endif // PRODUCTWIDGET_H
