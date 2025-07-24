#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QLabel>
#include <QPushButton>
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
    id_t getChatRoomId();
    void setChatRoomId(id_t roomId);
    void setInfo(id_t id , id_t roomId, QString category, QString name , qreal price, qint32 stock);

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



    int clicked_cnt = 0;

};

#endif // PRODUCTWIDGET_H
