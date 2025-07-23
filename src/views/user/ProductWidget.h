#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

namespace Ui {
class ProductWidget;
}

class ProductWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductWidget(QWidget *parent = nullptr);
    ~ProductWidget();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    Ui::ProductWidget *ui;
    QPoint m_dragStartPosition;

};

#endif // PRODUCTWIDGET_H
