#include "ProductWidget.h"
#include "ui_product_widget.h"


ProductWidget::ProductWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProductWidget)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
}

ProductWidget::~ProductWidget()
{
    delete ui;
}

void ProductWidget::mousePressEvent(QMouseEvent* event){
    if (event->button() == Qt::LeftButton) {
        m_dragStartPosition = event->pos();
    }
}

void ProductWidget::mouseMoveEvent(QMouseEvent* event){
    if (!(event->buttons() & Qt::LeftButton))
        return;

    if ((event->pos() - m_dragStartPosition).manhattanLength()
        < QApplication::startDragDistance())
        return;

    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData;

    // 위젯 정보를 MIME 데이터로 저장
    mimeData->setText(objectName());
    drag->setMimeData(mimeData);

    // 드래그 이미지 설정
    QPixmap pixmap = grab();
    drag->setPixmap(pixmap);

    Qt::DropAction dropAction = drag->exec(Qt::MoveAction);
}
